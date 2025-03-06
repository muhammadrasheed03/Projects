# California Neural Network

## Overview
This project implements a **Multi-Layer Perceptron (MLP)** to predict California housing prices using the **California Housing dataset** from `scikit-learn`. The model is trained using PyTorch and includes data preprocessing, training, validation, and evaluation steps.

## Technologies Used
- **Programming Language:** Python  
- **Machine Learning Framework:** PyTorch  
- **Data Processing:** scikit-learn, NumPy, Pandas  
- **Visualization:** Matplotlib, Seaborn  
- **Version Control:** Git, GitHub  

## Installation
1. **Clone the repository:**
   ```bash
   git clone https://github.com/muhammadrasheed03/Projects.git
   ```
2. **Navigate to the project directory:**
   ```bash
   cd Projects/California\ Neural\ Network
   ```
3. **Create a virtual environment (optional but recommended):**
   ```bash
   python -m venv venv
   source venv/bin/activate  # On Windows use: venv\Scripts\activate
   ```
4. **Install dependencies:**
   ```bash
   pip install -r requirements.txt
   ```

## Usage
1. **Run the training script:**
   ```bash
   python training.py
   ```
2. **Evaluate the trained model:**
   ```bash
   python evaluate.py
   ```
3. **Load and use the trained model:**
   ```python
   import torch
   from model import MLP

   model = MLP(input_size=8)
   model.load_state_dict(torch.load("best.pt"))
   model.eval()
   ```

## Dataset
- The dataset used is the **California Housing dataset**, which contains **8 numerical features** related to house prices in California.  
- More details: [California Housing Dataset](https://scikit-learn.org/stable/datasets/real_world.html#california-housing-dataset).



