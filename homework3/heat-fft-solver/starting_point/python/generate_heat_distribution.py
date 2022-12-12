#Implement a python script to generate a heat distribution within a 
# provided radius as given in 
# Equation5.hv(x,y) ={1ifx2+y2< R0otherwise(5), where R is a provided radius.
# 
# We also apply a boundary condition to the temperature field: 
# it shouldbe zero on the boundary of the domain and not evolve with time. 
# Explain in the README how you
# integrate this condition within the existing code

import sys 
import numpy as np
import argparse
import csv
import matplotlib.pyplot as plt

def run_display(
    x_coordinates : np.array(float),
    y_coordinates : np.array(float),
    input_heat_values : list
    )-> None:
    """
    Method to preview the heat distribution

    :param x_coordinates:  coordinates along the x axis
    :param y_coordinates:  coordinates along the y axis
    :param input_heat_values: heat distribution that is marked as 1 or 0
    
    """
    fig = plt.figure()
    axe = fig.add_subplot(1,1,1)
    for i in range(len(input_heat_values)):
         if input_heat_values[i] == 0:
             axe.scatter(x_coordinates[i],y_coordinates[i],color='green')
         else:
             axe.scatter(x_coordinates[i],y_coordinates[i],color='red')
    axe.set_aspect(1)
    plt.show()
    print ("Displaying the heat distribution")


def main (input_radius : float,
        input_x_domain : list,
        input_y_domain : list,
        input_x_divisions : int,
        input_y_divisions : int,
        input_display : bool,
        input_file_name : str
    ) -> None:
    
     """
     Initialize heat distribution within a provided radius

     :param input_radius:  radius of the circle
     :param input_x_domain:  interval of the x axis
     :param input_y_domain:  interval of the y axis
     :param input_x_divisions: number of divisions along the x axis
     :param input_y_divisions: number of divisions along the y axis
     :param input_display: boolean to display the heat distribution
     :param input_file_name: name of the output file
    
     """
    
     # main parameters
     heat_values = []
     x_coordinates = []
     y_coordinates = []
     theta_values = []
     is_bound = []
     interpolation_of_x = np.linspace(input_x_domain[0],input_x_domain[1],input_x_divisions)
     interpolation_of_y = np.linspace(input_y_domain[0],input_y_domain[1],input_y_divisions)
     
     
     #create output file
     with open(input_file_name, mode='w', newline='') as f:
         file_writer = csv.writer(f, delimiter = ',', quotechar='"',quoting=csv.QUOTE_MINIMAL)
         for i in range(len(interpolation_of_x)):
             for j in range(len(interpolation_of_y)):
                 #print("Hi")
                 x_coordinates.append(interpolation_of_x[i])
                 y_coordinates.append(interpolation_of_y[j])
                 heat_values.append(get_heat_distribution(interpolation_of_x[i],interpolation_of_y[j],input_radius))
                 theta_values.append(1)
                 is_bound.append(is_boundary(interpolation_of_x[i],interpolation_of_y[j],
                                             input_x_domain[0],input_x_domain[1],
                                             input_y_domain[0],input_y_domain[1]))
                 #print([interpolation_of_x[i],interpolation_of_y[j],theta_values[-1],heat_values[-1],is_bound[-1]])
                 file_writer.writerow([interpolation_of_x[i],interpolation_of_y[j],theta_values[-1],heat_values[-1],is_bound[-1]])
    


     #display the heat distribution        
     if input_display:
         #print(typeof(heat_values))
         run_display(x_coordinates,y_coordinates,heat_values)
        
    
   

    
def get_heat_distribution(x,y,r) -> bool:
    """
    Method to get the heat distribution within a provided radius
    
    :param x: float position
    :param y: float position
    :param r: float radius
    
    :return: 1 if x^2 + y^2 < r^2, 0 otherwise
    """
    
    if((x**2 + y**2) < r**2):
        return 1
    else:
        return 0

    
def is_boundary(x,y,x_0,x_1,y_0,y_1) -> bool:
    """
    Methond to check if a point is on the boundary of the domain
    
    :param x: float position
    :param y: float position
    :param x_0: float position of the left boundary
    :param x_1: float position of the right boundary
    :param y_0: float position of the bottom boundary
    :param y_1: float position of the top boundary
    
    :return: true or false depending if the points is on the boundary        
    
    """
    if((x==x_0) or (x==x_1) or (y==y_0) or (y==y_1)):
        return True
    else:
        return False

if __name__ == "__main__":
    # create command line parser
    parser = argparse.ArgumentParser(description="Generate heat distribution in CSV file, user must input the radius and domain")
    parser.add_argument("-r", nargs=1, default=[1], help="radius of the heat distribution", type=float)
    parser.add_argument("-x",nargs=2, default=[-1,1], help="x-domain, write two number <min,max>", type=float)
    parser.add_argument("-y",nargs=2, default=[-1,1], help="y-domain, write two number <min,max>", type=float)
    parser.add_argument("-cx", nargs=1,default=[32],help="number of points in x-direction", type=int)
    parser.add_argument("-cy", nargs=1,default=[32],help="number of points in y-direction", type=int)
    parser.add_argument("--display", default=False, action='store_true', help="display the values using the matplotlib")
    parser.add_argument("-f", nargs=1, default="heat_distribution.csv", help="output file name, user must add .csv ending", type=str)
    
    args = parser.parse_args()
    # if len(sys.argv) < 9:
    #     print(len(sys.argv))
    #     parser.print_usage()
    #     sys.exit()
        
    _input_radius : float = args.r[0]
    _input_x_domain : float = args.x
    _input_y_domain : float = args.y
    _input_x_divisions : int = args.cx[0]
    _input_y_divisions : int = args.cy[0]
    _input_display : bool = args.display
    _input_file_name : str = args.f

    
    # sanity check of the input arguments
    if _input_radius < 0:
        print("Radius must be a positive number")
        sys.exit()
    if _input_x_domain[0] > _input_x_domain[1]:
        print("x-domain must be <min,max>")
        sys.exit()
    if _input_y_domain[0] > _input_y_domain[1]:
        print("y-domain must be <min,max>")
        sys.exit()
    if _input_x_divisions < 1:
        print("x-divisions must be a positive integer")
        sys.exit()
    if _input_y_divisions < 1:
        print("y-divisions must be a positive integer")
        sys.exit()
    if _input_file_name[-4:] != ".csv":
        print("file name must end with .csv")
        sys.exit()
    
    # call the main function, where the values will be calculated

    main (input_radius = _input_radius,
        input_x_domain =_input_x_domain,
        input_y_domain = _input_y_domain,
        input_x_divisions = _input_x_divisions,
        input_y_divisions =_input_y_divisions,
        input_display = _input_display,
        input_file_name =_input_file_name
    )