#include "state.h"
#include <fstream>
#include <iomanip>  //need to use formatting manipulators
#include <vector>
#include <algorithm>

/*
Name:  Default Constructor
Pre-Conditon: The count, capacity, and the dynamic array (pop_DB) have not been initialized.
Post-Condition: The count, capacity, and the dynaic array (pop_DB) have been initialized.
Description:  The function initiailizes the state (private data) of the class state_class.It reads the data stored in the datafile "census2020_data.txt" into the dynamic array, pop_DB.  Initially, count is set to 0, capacity to 5, and pop_DB is allocated 5 cells.  If pop_DB become full,
              double_size is called, which doubles the capacity of pop_DB.
 **********************************************************************************/
state_class::state_class()
{
    //intially count, capacity, and pop_DB are initialized with the following values:
    string Sname;
    int space = 0;
    //double ss;
    count = 0;
    capacity = 5;
    pop_DB = new population_record[capacity];
    
    
    ifstream in;
    in.open("census2020_data.txt");
    if(in.fail())
    {
        cout << "File did not open" << endl;
    }
    while(!in.eof())
    {
        if(Is_Full())
        {
            double_size();
        }
        getline(in,Sname);
        for(int i = Sname.length() - 1; i >= 0; i--)
        {
            if(Sname[i] == ' ')
            {
                space = i;
                break;
            }
         }
        
        pop_DB[count].state_name = Sname.substr(0,space);
         
        pop_DB[count].population = std::stod(Sname.substr(space + 1,Sname.length() - (space - 1)));
         
        count++;
            
        
    }
    
    
    cout << "The default constructor has been called" << endl;
    in.close();
}

/*
Name: Copy constructor
Pre-Condition: Dynmaic array has not been copyed into org
Post-Condition: Dynmaic array has been copyed into org
Description: The function performs a deep copy of the formal parameter org.
**********************************************************************************/
state_class::state_class(const state_class & org)
{
    pop_DB = new population_record[capacity];
    count = org.count;
    capacity = org.capacity;
    
    for(int i = 0; i < org.count; i++)
    {
        pop_DB[i] = org.pop_DB[i];
    }
}

/*
Name: Destructor
Pre-Condition: Memory is still allocated to the dynmaic array and the free space and variables have not been initialized to zero
Post-Condition: Memory from the dynamic array STR has been de-allocated
Description: de-allocates all memory allocated to STR.  This will be the last function to be called (automatically by the compiler) before the program is exited.
*****************************************************************/
state_class::~state_class()
{
    delete [] pop_DB;
}

/*
Name: Double_Size
Pre-Condition: Capacity is equal to count
Post-Condition: Capacity has been doubled in size
Description: Capacity is being doubled in order to create more space for the dynamic array
********************************************************************************************************/
void state_class::double_size()
{
    capacity *= 2;
    population_record *temp = new population_record[capacity];
    
    for(int i = 0; i < count; i++)
    {
        temp[i] = pop_DB[i];
    }
    delete [ ] pop_DB;
    pop_DB = temp;
}

/*
Name:Operator+
Pre-Condition: Data has not been added into the file
Post-Condition: Data has been added into the file
Description: Operator+ adds another line of data to the
*************************************************************************************************************/
void state_class::operator+(const population_record& r)
{
    if(Is_Full())
    {
        double_size();
    }
    pop_DB[count].state_name = r.state_name;
    pop_DB[count].population = r.population;
    count++;
}

/*
Name: Search
Pre-Condition: Location of state needs to be located from the dynamic array
Post-Condition: Data has either been located or a -1 has been returned
Description: Locates state in pop_DB if it is there; otherwise -1 is returned
******************************************************************************************************************************************************/
int state_class::Search(const string& state)
{
    for(int i = 0; i < count; i++)
    {
        if(pop_DB[i].state_name == state)
        {
            return i;
        }
    }
    return -1;
}


/*
Name: Remove
Pre-Condition: Specific data from state has not been removed
Post-Condition: Data has been removed
Description: removes state from record in pop_DB
******************************************************************************************************************************************************/
void state_class::Remove(const string& state)
{
    int loc = Search(state);
    if(loc != -1)
    {
        for(int i = loc; i < count - 1; i++)
        {
            pop_DB[i] = pop_DB[i + 1];
        }
        count--;
    }
    
}


/*
Name: Print_ALL_To_File
Pre-Condition:
Post-Condition:
Description:
******************************************************************************************************************************************************/
void state_class::Print_ALL_To_File(const string& filename)
{
    ofstream out;
    out.open("datafile");
    for(int i = 0; i < count; i++)
    {
        out.setf(ios::showpoint);
        out.precision(2);
        out.setf(ios::fixed);
        
        out << left << setw(15) << pop_DB[i].state_name;
        out << right << setw(15) << pop_DB[i].population << endl;
    }
}
/*
Name: Print_All
Pre-Condition: Data has not been outputed to the screen
Post-Condition: Data has been outputed to te screen
Description: This function is going to print all fields to the screen
*********************************************************************************************************/
void state_class::Print_ALL()
{
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout.setf(ios::fixed);
    
    for(int i = 0; i < count; i++)
    {
    cout << left << pop_DB[i].state_name;
    cout << right << setw(15) << pop_DB[i].population << endl;
    }

}


/*
Name: Print_Range
Pre-Condition: Has not printed states between certain population range
Post-Condition: Has printed states that full under the criteria.
Description: prints all the fields of all the population records stored in pop_DB with a population between min and max to the screen
******************************************************************************************************/
void state_class::Print_Range(const int min, const int max)
{
    for(int i = 0; i < count; i++)
    {
        if(pop_DB[i].population >= min && pop_DB[i].population <= max)
        {
            cout << left << pop_DB[i].state_name;
            cout << right << setw(15) << pop_DB[i].population << endl;
        }
    }
}


/*
Name: State count
Pre-Condition: States have not been totaled up between the min and max range
Post-Condition: The total number of states between the range has been addes up
Description://returns the total number of states with a population between min and max, inclusive.
****************************************************************************************************/
int state_class::State_Count(const int min, const int max)
{
    int state_number = 0;
    
    for(int i = 0; i < count; i++)
    {
        if(pop_DB[i].population >= min && pop_DB[i].population <= max)
        {
            state_number++;
        }
    }
    return state_number;
}

/*
Name: Sort
Pre-Condition: Data is not in alphabetical order
Post-Condition: Data is in alphbetical order
Description: sorts the array pop_DB in alphabetical order based on state_name field using insertion sort algorithm
******************************************************************************************************************************************************/
void state_class::Sort()
{
    for(int i = 0; i < count - 1; i++)
    {
        population_record key = pop_DB[i];
        int j = i - 1;
        
        while(j >= 0 && pop_DB[j].state_name > key.state_name)
        {
            pop_DB[j + 1] = pop_DB[j];
            j = j - 1;
        }
        pop_DB[j + 1] = key;
    }
                       
    
    

}

