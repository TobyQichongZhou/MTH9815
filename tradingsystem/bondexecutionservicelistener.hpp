/**
 * bondexecutionservicelistener.hpp
 * Defines BondExecutionServiceListener to listen data pasing to
 * BondExecutionService
 * 
 * @author Qichong Zhou
 */
#ifndef BOND_EXECUTION_SERVICE_LISTENER_HPP
#define BOND_EXECUTION_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "bondexecutionservice.hpp"
#include "bondalgoexecutionservice.hpp"

/**
 * BondExecutionServiceListener to listen data passing to BondExecution Servicing
 * from BondAlgoExecutionService
 */
class BondExecutionServiceListener: public ServiceListener<AlgoExecution> {

private:
    BondExecutionService* bes;

public:
    //ctor
    BondExecutionServiceListener(BondExecutionService * _bes) {
        bes = _bes;
    }

    //override pure virtual functions
    virtual void ProcessAdd(AlgoExecution& data) override{
        auto executionorder = data.GetExecutionOrder();

        bes->ExecuteOrder(executionorder, BROKERTEC);
    }

    virtual void ProcessRemove(AlgoExecution& data) override {}
    virtual void ProcessUpdate(AlgoExecution& data) override {}


};

#endif
