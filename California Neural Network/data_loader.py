import torch
from sklearn.datasets import fetch_california_housing
from torch.utils.data import DataLoader, TensorDataset, random_split

def load_data():
    data = fetch_california_housing()
    inputs = torch.tensor(data.data, dtype=torch.float32)
    targets = torch.tensor(data.target, dtype=torch.float32)

    # Normalize data
    mean, std = inputs.mean(dim=0), inputs.std(dim=0)
    inputs = (inputs - mean) / std

    mean, std = targets.mean(), targets.std()
    targets = (targets - mean) / std

    dataset = TensorDataset(inputs, targets)
    train_ds, val_ds, test_ds = random_split(dataset, [0.8, 0.1, 0.1])
    
    train_loader = DataLoader(train_ds, batch_size=256, shuffle=True)
    val_loader = DataLoader(val_ds, batch_size=256, shuffle=False)
    test_loader = DataLoader(test_ds, batch_size=256, shuffle=False)

    return train_loader, val_loader, test_loader
