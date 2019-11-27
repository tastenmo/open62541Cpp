#ifndef TESTMETHOD_H
#define TESTMETHOD_H

#include <servermethod.h>
class TestMethod : public Open62541::ServerMethod
{
    Open62541::NodeId eventType;
public:
    TestMethod() : Open62541::ServerMethod("TriggerEvent",0,0)
    {

    }

    bool initialise(Open62541::Server &server);
    /*!
        \brief callback
        \return
    */
    virtual UA_StatusCode callback(Open62541::Server &/*server*/,
                                   const UA_NodeId */*objectId*/,
                                   size_t /*inputSize*/,
                                   const UA_Variant * /*input*/,
                                   size_t /*outputSize*/,
                                   UA_Variant * /*output*/);
};

#endif // TESTMETHOD_H
