import argparse
import numpy as np
import torch
import torchvision
import os
import time

from collections import OrderedDict
from torch import nn
from torch import optim
from torch.autograd import Variable
from torchvision import datasets, models, transforms



def main():
    args = get_arguments()
    input_layers = None
    output_size = None
    if not os.path.exists(args.save_dir):
        os.makedirs(args.save_dir)
    save_dir = os.path.join(args.save_dir, 'checkpoint.pth')
    
    if args.model == 'densenet121':
        input_layers = 1024
        output_size = 102
        model = models.densenet121(pretrained=True)
        for param in model.parameters():
            param.requires_grad = False
            input_size = 1024 
            hidden_sizes = [1800, 600,400]
            output_size = 102
        classifier = nn.Sequential(OrderedDict([
                      ('fc1', nn.Linear(input_size, hidden_sizes[0])),
                      ('relu1', nn.ReLU()),
                      ('fc2', nn.Linear(hidden_sizes[0], hidden_sizes[1])),
                      ('relu2', nn.ReLU()),
                      ('fc3', nn.Linear(hidden_sizes[1],hidden_sizes[2])),
                      ('relu3', nn.ReLU()),
                      ('fc4', nn.Linear(hidden_sizes[2],output_size)),
                      ('output', nn.LogSoftmax(dim=1))]))
        
    elif args.model == 'vgg19':
        input_layers = 25088
        output_size = 102
        model = models.vgg19(pretrained=True)
        for param in model.parameters():
            param.requires_grad = False
        classifier = nn.Sequential(OrderedDict([
                                        ('input',  nn.Linear(25088, 5000)),
                                        ('relu1',  nn.ReLU()),
                                        ('dropout1',  nn.Dropout(0.5)),
                                        ('linear2',  nn.Linear(5000, 500)),
                                        ('relu2',  nn.ReLU()),
                                        ('linear3', nn.Linear(500, 102)),
                                        ('output', nn.LogSoftmax(dim=1))
                                       ])) 
    
    model.classifier = classifier
    data_loaders, image_datasets, data_transforms = data_parser(args.data_path)
    
    if args.cuda:
        model = model.cuda()
    
    criterion = nn.NLLLoss()
    optimizer = optim.Adam(model.classifier.parameters(), lr=args.lr)
    train_model(model, data_loaders, criterion=criterion, optimizer=optimizer, epochs=int(args.epochs), cuda=args.cuda)
    validate_model(model, data_loaders[2], cuda=args.cuda)

    checkpoint = {'input_size': input_layers,
                  'output_size': output_size,
                  'epochs': args.epochs,
                  'learning_rate':args.lr,
                  'batch_size': 64,
                  'data_transforms': data_transforms,
                  'model': model,
                  'classifier': classifier,
                  'optimizer': optimizer.state_dict(),
                  'state_dict': model.state_dict(),
                  'class_to_idx': image_datasets[0].class_to_idx
                }

    torch.save(checkpoint, 'checkpoint.pth')
    

def get_arguments():
    parser = argparse.ArgumentParser()
    
    parser.add_argument("--save_dir", action="store", dest="save_dir", default="." , help = "Set directory to save checkpoints")
    parser.add_argument("--model", action="store", dest="model", default="densenet121" , help = "Set architechture('densenet121' or     'vgg19')")
    parser.add_argument("--learning_rate", action="store", dest="lr", default=0.001 , help = "Set learning rate")
    parser.add_argument("--hidden_units", action="store", dest="hidden_units", default=512 , help = "Set number of hidden units")
    parser.add_argument("--epochs", action="store", dest="epochs", default=5 , help = "Set number of epochs")
    parser.add_argument("--gpu", action="store_true", dest="cuda", default=True , help = "Use CUDA for training")
    parser.add_argument('data_path', action="store")
    
    return parser.parse_args()

def data_parser(data_path):    
    train_dir = data_path + '/train'
    valid_dir = data_path + '/valid'
    test_dir = data_path + '/test'
    
    batch_size = 64
    #from github samuelharvard
    data_transforms = [transforms.Compose([transforms.Resize(256), 
                                         transforms.CenterCrop(224),
                                         transforms.ToTensor(),
                                         transforms.Normalize([0.485, 0.456, 0.406], 
                                                              [0.229, 0.224, 0.225])]),

                     transforms.Compose([transforms.RandomRotation(30),
                                           transforms.RandomResizedCrop(224),
                                           transforms.RandomHorizontalFlip(),
                                           transforms.ToTensor(),
                                           transforms.Normalize([0.485, 0.456, 0.406],
                                                                [0.229, 0.224, 0.225])])]

    image_datasets = [datasets.ImageFolder(train_dir, transform=data_transforms[1]),   
                      datasets.ImageFolder(valid_dir, transform=data_transforms[0]),   
                      datasets.ImageFolder(test_dir,  transform=data_transforms[0])]   

    dataloaders = [torch.utils.data.DataLoader(image_datasets[0], batch_size=batch_size, shuffle=True), 
                   torch.utils.data.DataLoader(image_datasets[1], batch_size=batch_size),            
                   torch.utils.data.DataLoader(image_datasets[2], batch_size=batch_size)]               
    
    return dataloaders, image_datasets, data_transforms

def train_model(model, dataloaders, criterion, optimizer, epochs=10, cuda=False):
    start_time = time.time()
    steps = 0
    
    print_every = 5
    
    if cuda and torch.cuda.is_available:
        model.cuda()
    else:
        model.cpu()

    for e in range(epochs):
        running_loss = 0
        for ii, (inputs, labels) in enumerate(dataloaders[0]):
            inputs, labels = Variable(inputs), Variable(labels)
            steps += 1
            
            if cuda:
                inputs, labels = inputs.cuda(), labels.cuda()
            
            optimizer.zero_grad()
            outputs = model.forward(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            
            running_loss += loss.item()
            
            if steps % print_every == 0:
                model.eval()
            
                accuracy = 0
                validation_loss = 0
            
                for ii, (images, labels) in enumerate(dataloaders[1]):
            
                    inputs = Variable(images, volatile=True)
                    labels = Variable(labels, volatile=True)
        
                    if cuda:
                        inputs, labels = inputs.cuda(), labels.cuda()
        
                    output = model.forward(inputs)
                    validation_loss += criterion(output, labels).item()
                    ps = torch.exp(output).data
                    equality = (labels.data == ps.max(1)[1])
                    accuracy += equality.type_as(torch.FloatTensor()).mean()

                print("Epoch: {} / {}.. ".format(e+1, epochs),
                      "Training Loss: {:.3f}.. ".format(running_loss/print_every),
                      "Validation Loss: {:.3f}.. ".format(validation_loss/len(dataloaders[1])),
                      "Validation Accuracy: {:.3f}".format(accuracy/len(dataloaders[1])))

                running_loss = 0
                model.train()
                
    elapsed_time = time.time() - start_time
    print('Elapsed Time: {:.0f}m {:.0f}s'.format(elapsed_time//60, elapsed_time % 60))
    
  
def validate_model(model, dataloaders, cuda=False):
    model.eval()
    accuracy = 0

    if cuda:
        model.cuda()
    else:
        model.cpu()

    for ii, (images, labels) in enumerate(dataloaders):
        inputs = Variable(images, volatile=True)
        labels = Variable(labels, volatile=True)

        if cuda:
            inputs, labels = inputs.cuda(), labels.cuda()

        output = model.forward(inputs)
        ps = torch.exp(output).data
        equality = (labels.data == ps.max(1)[1])
        accuracy += equality.type_as(torch.FloatTensor()).mean()

    print("Testing Accuracy: {:.3f}".format(accuracy/len(dataloaders)))
    

main()