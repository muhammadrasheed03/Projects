# Checkout Line  

## Overview  
This project simulates a simple market checkout line with one cashier. Customers arrive with a certain probability, each having a random number of items in their basket. The cashier processes one item per tick, and when a customer's basket is empty, they leave the line. The simulation is driven by an event list generated from a file.  

## Technology Used  
- **Python**  
- Object-Oriented Programming (OOP)  
- File Handling  
- Randomization for simulation  

## Usage Instructions  

1. **Clone the repository:**  
   ```bash
   git clone https://github.com/muhammadrasheed03/Projects.git
   cd Projects/Checkout\ Line
   ```

2. **Generate an event file (optional):**  
   You can create a custom event file to simulate customer arrivals and item counts.  
   ```python
   from checkout import generateEventsFile
   generateEventsFile(N=50, perc=30, maxItems=10, fileName="events.txt")
   ```
   - `N`: Number of time steps in the simulation  
   - `perc`: Probability (in %) of a new customer arriving  
   - `maxItems`: Maximum number of items a customer can have  
   - `fileName`: Name of the generated file  

3. **Run the simulation:**  
   ```python
   from checkout import generateEventListFromFile, simulateCheckoutLine
   events = generateEventListFromFile("events.txt")
   simulateCheckoutLine(events)
   ```

4. **Observe the output** as customers enter, move through, and leave the checkout line.  
