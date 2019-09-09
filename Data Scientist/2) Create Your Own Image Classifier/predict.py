import pickle
import argparse
import json
import numpy as np
import torch

from PIL import Image
from torch.autograd import Variable

def main():
    args = get_arguments()
    cuda = args.cuda
    model = load_checkpoint(args.checkpoint, cuda)
    model.idx_to_class = dict([v,k] for k, v in model.class_to_idx.items())
    
    with open(args.categories, 'r') as f:
        cat_to_name = json.load(f)
      
    prob, classes = predict(args.input, model, args.cuda, topk=int(args.top_k))
    print([cat_to_name[x] for x in classes])
    
    
def get_arguments():
    parser = argparse.ArgumentParser(description = '')
    parser.add_argument("input", action="store")
    parser.add_argument("checkpoint", action="store")
    parser.add_argument("--top_k", action="store", dest="top_k", default=5, help="Number of top results you want to view.")
    parser.add_argument("--category_names", action="store", dest="categories", default="cat_to_name.json", help="Top results for viewing.")
    parser.add_argument("--cuda", action="store_true", dest="cuda", default=False, help="Set Cuda True for using the GPU")
    return parser.parse_args()

        
def process_image(image):
    image_ratio = image.size[1] / image.size[0]
    image = image.resize((256, int(image_ratio*256)))
    half_width = image.size[0] / 2
    half_height = image.size[1] / 2
    image = image.crop((half_width - 112,half_height - 112, half_width + 112, half_height + 112))
    image = np.array(image)
    image = image/255
    mean = np.array([0.485, 0.456, 0.406])
    std_dev = np.array([0.229, 0.224, 0.225])
    image = (image - mean) / std_dev
    image = image.transpose((2, 0, 1))
    
    return torch.from_numpy(image)

    
def predict(image_path, model, cuda, topk):
    if cuda:
        model.cuda()
    else:
        model.cpu()
    image = None
    model.eval()
    with Image.open(image_path) as img:
        image = process_image(img)     
    image = Variable(image.unsqueeze(0), volatile = True)
    if cuda:
        image = image.cuda()
    output = model.forward(image.float())
    ps = torch.exp(output)
    prob, idx = ps.topk(topk)
    return [print(q,end = "\n") for q in prob.detach().numpy()[0]], [model.idx_to_class[x] for x in idx.detach().numpy()[0]] 

def load_checkpoint(filepath, cuda):
    if cuda:
        checkpoint = torch.load(filepath)
    else:
        checkpoint = torch.load(filepath, map_location=lambda storage, loc: storage)
    model = checkpoint['model']
    model.classifier = checkpoint['classifier']
    model.load_state_dict(checkpoint['state_dict'])
    model.class_to_idx = checkpoint['class_to_idx']
    optimizer = checkpoint['optimizer']
    return model

main()