                                                # 112_managment_system

### Program structure
The programm implements a basic emergency number system (112 - in most european countries), which handles a set of basic
operations. The aplication works with incidents who are inserted using the ADD_INCIDENT option, and units who are defined at the
start. Both input and output are processed thorugh file(tema1.in & tema1.out). Every incident is categorized in three levels
by urgency (low/medium and high). The incidents and interventions are stored in a circular double linked list with a sentinel,
while processing urgency and available units using queues. We also store a history of all interventions using a stack. We can DISPATCH a unit, mark an incident solved, show details of an incident, showing all interventions and so on

### Files description
The program is structured in 4 files, which include:
    - main.c - parsing every option and handling it
    - structs.c - methods and definitons (header) for specific structures of the programm (Incident/Unit/Intervention)
    - queueStack.c - methods and definitions (header) for data structures such as queue and stack
    - linkedList.c - methods for double circular linked lists with sentinel

### Implementation time & logs
This project helped me to understand better how data structures such as linked lists, queues and stacks work,
while making me think about modularity, dividing the logic into general-use functions for every data structure. The implementation took 6 to 10 hrs (not sure about that :)). A big challange was making the program memory efficient, by freeing every dinamically alocated data at the right time. I also learnt more about using tools for memory such as valgrind.