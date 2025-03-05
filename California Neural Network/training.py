import torch
from torch import nn
from model import MLP
from data_loader import load_data

def train_model():
    train_loader, val_loader, test_loader = load_data()
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = MLP().to(device)

    criterion = nn.MSELoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=1e-3)
    scheduler = torch.optim.lr_scheduler.StepLR(optimizer, step_size=10, gamma=0.7)

    best_val_loss = float("inf")
    best_epoch = 0

    for epoch in range(100):
        model.train()
        train_loss = 0.0
        for inputs, targets in train_loader:
            inputs, targets = inputs.to(device), targets.to(device)
            outputs = model(inputs)
            loss = criterion(outputs.flatten(), targets)
            
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            train_loss += loss.item()
        
        val_loss = evaluate_model(model, val_loader, criterion, device)
        if val_loss < best_val_loss:
            best_val_loss = val_loss
            best_epoch = epoch
            torch.save(model.state_dict(), "best.pt")

        if epoch - best_epoch >= 20:
            print(f"Stopping early at epoch {epoch}")
            break

        scheduler.step()

def evaluate_model(model, loader, criterion, device):
    model.eval()
    loss = 0.0
    with torch.no_grad():
        for inputs, targets in loader:
            inputs, targets = inputs.to(device), targets.to(device)
            outputs = model(inputs)
            loss += criterion(outputs.flatten(), targets).item()
    return loss / len(loader)
