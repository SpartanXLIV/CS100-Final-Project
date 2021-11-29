#include <iostream>
#include "TaskMaster.h"

TaskMasterNode::TaskMasterNode() 
{
    taskID = "none";
    taskDesc  = "none";
    taskType = "none";
    totalTasks = 0;
    nextNodePtr = 0;
}

TaskMasterNode::TaskMasterNode(string initID, string initDesc, string initType, int initTotal, TaskMasterNode* nextLoc)
{
    taskID = initID;
    taskDesc = initDesc;
    taskType = initType;
    totalTasks = initTotal;
    nextNodePtr = nextLoc;
}

void TaskMasterNode::InsertAfter(TaskMasterNode* ptr)
{
    TaskMasterNode* temp = nullptr; 

    temp = this->nextNodePtr;
    this->nextNodePtr = ptr;
    ptr->nextNodePtr = temp;
}

void TaskMasterNode::SetNext(TaskMasterNode* ptr) 
{
    nextNodePtr = ptr;
}

TaskMasterNode* TaskMasterNode::GetNext()
{
    return this->nextNodePtr;
}

string TaskMasterNode::GetID() const
{
    return taskID;
}

string TaskMasterNode::GetTaskDesc() const 
{
    return taskDesc;
}

string TaskMasterNode::GetTaskType() const
{
    return taskType;
}

int TaskMasterNode::GetTotalTasks() const
{
    return totalTasks;
}

void TaskMasterNode::PrintTaskMasterNode()	
{
    cout << "Task ID: " << taskID << endl;
    cout << "Task Type: " << taskType << endl; 
    cout << "Task Description : " << taskDesc << endl;
}


