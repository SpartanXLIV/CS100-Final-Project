#include <iostream>
#include <string>
#include <iomanip>

#include "TaskMaster.h"
#include "TaskMaster.cpp"

using namespace std;

void PrintMenu(const string userName)
{
    char menuOp = ' ';
    string taskID;
    string taskDesc;
    string taskType;
    int totalTasks = 0;

    int numNodes = 0;
    int taskPosition = 0;
    int newPosition = 0;
    int taskCount = 0;

    TaskMasterNode* newTask = 0;
    TaskMasterNode* currNode = 0;
    TaskMasterNode* taskNode = 0;
    TaskMasterNode* prevNode = 0;
    TaskMasterNode* insertPosNode = 0;
    TaskMasterNode* headNode = 0;
    TaskMasterNode* tailNode = 0;
    TaskMasterNode* currPrintNode = 0;

    // Output menu option, prompt users for valid selection
    while (menuOp != 'q')
    {
        menuOp = ' ';
        cout << userName << "'s TASK MENU" << endl;
        cout << "a - Add a Task" << endl;
        cout << "r - Remove a Task" << endl;
        cout << "c - Change priority of a Task" << endl;
        cout << "s - Sort Tasks by task type" << endl;
        cout << "t - Total # of tasks to complete" << endl;
        cout << "o - Output all tasks by priority" << endl;
        cout << "q - Quit" << endl << endl;

        while (menuOp != 'a' && menuOp != 'r' && menuOp != 'c' &&
            menuOp != 's' && menuOp != 't' && menuOp != 'o' && menuOp != 'q')
        {
            cout << "Choose an option:" << endl;
            cin >> menuOp;
        }
	

	if (menuOp == 'a')
        {
            // Prompt user for task information
            cout << "ADD TASK" << endl;
            cout << "Enter Task's unique ID \n(This will be needed to delete a task so make it something short)\n(ex. 1, 2, 3, or a, b c, etc:" << endl;
            cin >> taskID;

	    cout << "What type of task will this be? \np - personal\nw - work\na - academic:" << endl;
            cin.ignore(); //removing this ignore fixed firsr char deletion error
            getline(cin, taskType);

            cout << "Enter Task description:" << endl;
            // cin.ignore();
	    getline(cin, taskDesc);

            totalTasks = 1;	//increase total tasks by 1

            
            newTask = new TaskMasterNode(taskID, taskDesc, taskType, totalTasks);
            if (headNode == nullptr)
            {
                tailNode = newTask;
                headNode = tailNode;
            }
            else
            {
                tailNode->SetNext(newTask);
                tailNode = newTask;
            }

            cout << endl;


        }

        if (menuOp == 'r')
        {
            string currTaskID;
            cout << "REMOVE TASK" << endl;
            cout << "Enter the task's unique ID:" << endl;
            cin >> currTaskID;
            
            for (currNode = headNode; currNode != nullptr; currNode = currNode->GetNext())
            {
                if (currTaskID == currNode->GetID())
                {
                    if (currNode == headNode) //head
		    {
                        cout << "\"" << currNode->GetTaskDesc() << "\"" << " removed." << endl;
                        taskNode = headNode->GetNext();
                        delete headNode;
                        headNode = taskNode;
                        break;
                    }
                }
		
		if (currNode->GetNext()->GetID() == currTaskID)
                {
                    if (currNode->GetNext() == tailNode) //tail
		    {
                        cout << "\"" << currNode->GetNext()->GetTaskDesc() << "\"" << " removed." << endl;
                        taskNode = currNode->GetNext();
                        currNode->SetNext(taskNode->GetNext());
                        delete tailNode;
                        tailNode = currNode;
                        break;
                    }
                    else
                    {
                        cout << "\"" << currNode->GetNext()->GetTaskDesc() << "\"" << " removed." << endl; 
			taskNode = currNode->GetNext();
                        currNode->SetNext(taskNode->GetNext());
                        delete taskNode;
                        break;
                    }
                }
                    
            }
            cout << endl;
        }

        if (menuOp == 'c')
        {
            cout << "CHANGE PRIORITY OF TASK" << endl;
            cout << "Enter task's current position:" << endl;
            insertPosNode = nullptr;
            int count, taskPosition;
            cin >> taskPosition;
            cout << "Enter new position for task:" << endl;
            int newPos;
            cin >> newPos;
            
            int countTasks = 0;
            for (currNode = headNode; currNode != nullptr; currNode = currNode->GetNext()) //Loop that counts total number of tasks
	    {
                ++countTasks;
            }
            
            if (taskPosition == 1) //Base case that moves headNode
	    {
                insertPosNode = headNode;
                headNode = headNode->GetNext();
            }
            
            else if (taskPosition == countTasks) //Base case that moves the tailnode
	    {
                insertPosNode = tailNode;

                //for loop that moves tail node;
                for (currNode = headNode; currNode->GetNext()->GetNext() != nullptr; currNode = currNode->GetNext())
                {
                    tailNode = currNode;
                }
                tailNode = tailNode->GetNext();
                tailNode->SetNext(nullptr);
            }
            else
            {
                count = 1;
                for (currNode = headNode; currNode != nullptr; currNode = currNode->GetNext())
                {
                    if (count == taskPosition - 1) {
                        insertPosNode = currNode->GetNext();
                        currNode->SetNext(currNode->GetNext()->GetNext());
                    }
                    count = count + 1;
                }
            }

	    count = 1;
            if (newPos == 1)
            {
                TaskMasterNode* temp = headNode;
                headNode = insertPosNode;
                insertPosNode->SetNext(temp);
            }
            else
            {
                for (currNode = headNode; currNode != nullptr; currNode = currNode->GetNext())
                {
                    if (count == newPos - 1)
                    {
                        currNode->InsertAfter(insertPosNode);
                    }
                    count = count + 1;
                }
            }
            cout << "\"" << insertPosNode->GetTaskDesc() << "\"" << " moved to position " << newPos << endl;
            cout << endl;
        }

        if (menuOp == 's')
        {
            cout << "SORT TASK BY TASK TYPE" << endl;
            cout << "Enter the task type \n(p,w, or a):" << endl;
            cout << endl;

            string type;
            cin.ignore();
            getline(cin, type);
            int taskNum = 1;
            for (currNode = headNode; currNode != nullptr; currNode = currNode->GetNext())
            {
                if (currNode->GetTaskType() == type)
                {
                    cout << taskNum << "." << endl;
                    currNode->PrintTaskMasterNode();
                    cout << endl;
                }
                taskNum = taskNum + 1;
            }
        }

        if (menuOp == 't')
        {
            cout << "TOTAL # OF TASKS TO COMPLETE" << endl;
            if (headNode == nullptr)  //base case incase head is empty
	    {
                cout << "You have no tasks to complete!" << endl;
            }
            else
            {
		taskCount = 0;	//need to reset to 0 everytime or else numbers add up
		
                for (currNode = headNode; currNode != nullptr; currNode = currNode->GetNext())
                {
                    taskCount = taskCount + currNode->GetTotalTasks();
                }
                cout << "Total: " << taskCount << " task(s) remaining" << endl;
            }
            cout << endl;
        }

        if (menuOp == 'o')
        {
            cout << "ALL OF " << userName << "'s TASKS BY PRIORITY" << endl;
            if (headNode == nullptr)
            {
                cout << "There are no tasks to complete!" << endl;
            }
            else 
            {
                int taskNum = 1;
                for (currNode = headNode; currNode != nullptr; currNode = currNode->GetNext()) 
                {
                    cout << taskNum << "." << endl;
                    currNode->PrintTaskMasterNode();

                    if (currNode->GetNext() != nullptr)
                    {
                        cout << endl;
                    } 
                    taskNum = taskNum + 1;
                }
            }
            cout << endl;
        }
     }	//check
}//check

	int main()
        {
            string userName;
            // Prompt user for Username title
            cout << "Please enter your name:" << endl;
            getline(cin, userName);
            cout << endl;
            // Output task list menu options
            PrintMenu(userName);
            return 0;
        }




