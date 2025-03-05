################################################################################
#                                                                              #
#                       Simulation of a Simple Market                          #
#                                                                              #
################################################################################

import random
import os.path

# The following function is useful and can be used as is;  there is no 
# reason to change it. 

def addCustomer(percent):
    """This function returns True with a certain probability.  For
    example, if percent is 35, then this returns True 35% of the 
    times you call it and returns False 65% of the time. This is 
    a useful trick in a simulation. """
    return random.randint(0, 99) < percent

def generateEventsFile( N, perc, maxItems, fileName ):
    """Create a file of N lines to drive the simulation.  Each line in the
      file contains a single non-negative integer in range
      [0...maxItems].  Lines are non-zero perc percentage of the time.
      Use the function addCustomer( percent) to decide whether the
      item should be zero or a random integer between 1 and maxItems,
      inclusive.  The idea is that if a line is zero, no new customer
      has arrived during that clock tick.  Otherwise, a new customer
      has arrived at the cashier line with that many items in their
      basket.  Remember to close the file."""
    with open(fileName, 'w') as file:
        for _ in range(N):
            if addCustomer(perc):
                file.write(f"{random.randint(1, maxItems)}\n")
            else:
                file.write("0\n")

def generateEventListFromFile( filename ):
    """Given a filename containing events, generate a list of the events
       suitable for the simulateCheckoutLine function.  Be sure to
       check that the file exists and print an error message and exit
       if not."""
    if not os.path.exists(filename):
        print(f"Error: File '{filename}' does not exist.")
        exit()
    with open(filename, 'r') as file:
        return [int(line.strip()) for line in file]

############################## Customer Class ############################## 

class Customer:
    def __init__(self, custNum, itemCount):
        """A new customer is assigned a customer number and also a number of
        items in their basket.
        """
        self.custNum = custNum
        self.itemCount = itemCount

    def getCustomerNumber(self):
        """Getter for the customer's number."""
        return self.custNum

    def getItemsCount(self):
        """Getter for the customer's current count of items."""
        return self.itemCount

    def decrementItemsCount(self):
        """Ring up (remove) one item from this customer's basket. 
        Typically, we'll only call this on the first customer in line."""
        self.itemCount -= 1

    def customerFinished(self):
        """Boolean function indicating that this customer will depart on 
        the current tick, i.e., there are zero items in their basket.  
        Typically we'll only call this on the first customer in line."""
        return self.itemCount == 0

    def __str__(self):
        """If this is customer n with k items in basket,
        return 'Cn(k)' """
        return f"C{self.custNum}({self.itemCount})"

############################## CheckoutLine Class ############################## 

class CheckoutLine:
    """A checkout line is implemented as a list with customers added at the front
    (L[0]) and removed from the rear (L[-1]).  Customers enter and
    move through the line.  At each tick, one item is removed from the
    basket of the first customer in line.  When their basket becomes
    empty, the first customer departs the line."""
   
    def __init__(self):
        """ Open a new line, with no customers initially. """
        self.line = []

    def __len__(self):
        """Return the current length of the line."""
        return len(self.line)

    def firstInLine(self):
        """ Return the first customer in the line."""
        return self.line[-1] if self.line else None

    def customerJoinsLine(self, cust):
        """ Add a new customer at the rear of the line.  Print a
            message indicating that the customer joined. """
        self.line.insert(0, cust)
        print(f"Customer C{cust.getCustomerNumber()} joining line.")

    def customerLeavesLine(self):
        """ The first customer in line departs.  Remove the customer
            from the line and print a message. """
        if self.line:
            cust = self.line.pop()
            print(f"Customer C{cust.getCustomerNumber()} leaving line.")

    def advanceLine(self):
        """ If the line is empty, don't change anything.  Otherwise,
            remove one item from the basket of the first customer in
            line.  If their basket becomes empty, they leave the
            line. (Use the previous methods to implement this.)"""
        if self.line:
            first_customer = self.line[-1]
            first_customer.decrementItemsCount()
            if first_customer.customerFinished():
                self.customerLeavesLine()

    def __str__(self):
        """ Return a string that shows the current state of the line. """
        return "   Line: [ " + " ".join(str(cust) for cust in reversed(self.line)) + " ]"

############################## Driver for the Simulation ############################## 
# The following function takes a list of events (non-negative integers) and drives
# the simulation based on the items in this list. 

def simulateCheckoutLine(eventList):
    """This is the driver program for this system.  We monitor the
        progress of customers in the checkout line.  The eventList
        decides when a new customer is added with how many items in
        their cart. Customers are numbered as they enter. At each tick
        of the simulator clock (each new item in eventList), the
        cashier processes one item in the basket of the first
        customer."""
    print("Simulating a simple market, with one cashier.")
    checkout_line = CheckoutLine()
    customer_number = 1

    for step, event in enumerate(eventList, start=1):
        print(f"\nStep: {step}")
        checkout_line.advanceLine()

        if event > 0:
            new_customer = Customer(customer_number, event)
            checkout_line.customerJoinsLine(new_customer)
            customer_number += 1

        print(checkout_line)
