#ifndef TASKMASTER_H
#define TASKMASTER_H
#include <string>

using namespace std;
class TaskMasterNode 
{
public:
    TaskMasterNode();
    TaskMasterNode(string initID, string initDesc, string initType, int initTotal, TaskMasterNode* nextLoc = 0);

    void InsertAfter(TaskMasterNode* ptr);
    void SetNext(TaskMasterNode* nodePtr);

    string GetID() const;
    string GetTaskDesc() const;
    string GetTaskType() const;
    int GetTotalTasks() const;
    TaskMasterNode* GetNext();
    void PrintTaskMasterNode();	

private:
    string taskID;
    string taskDesc;
    string taskType;
    int totalTasks;
    TaskMasterNode* nextNodePtr;
};
#endif
