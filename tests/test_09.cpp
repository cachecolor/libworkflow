#include <iostream>
#include <core/workflow.h>
#include <core/action.h>
#include <core/state_machine.h>
#include <core/bindings.h>
#include <tests/common/test_client.h>
#include <tests/common/actions/do_next.h>
#include <tests/common/contexts/some_context.h>
#include <tests/common/actions/some_actions.h>
#include <service/actor.h>
#include <service/controller_manager.h>
#include <core/controller.h>

/**
 Test 9 is a Workflow input Test. This is a simple A workflow, where A allows a context input. We won't provide it but it shall work.
 */


void TestClient::prepareTest() {
    BOOST_LOG_SEV(logger, Info) << logActor() << "Adding workflow";
    WorkflowPtr workflow(new Workflow("test-9"));
    auto sm = workflow->getStateMachine();
    sm->addAction(0, new SomeAllowed(), {
        OutputBinding(0, "", (int32_t)Step::Finish, "")
    });
    sm->addInput(InputBinding("some_data", 0, "some_data"));
    
    // registering it.
    ControllerManager::getInstance()->getController("default")->addWorkflow(workflow);
    
    RequestPtr request(new Request(Target("test-9"), Target("test_result")));
    request->getTarget().workflow = "test-9";
    
    expect(request, ETestResult::Success);
    publishRequest(request);
    
    std::string str;
    workflow->str_save(str);
    std::ofstream fs;
    fs.open("jsons/test_9.json");
    fs << str;
    fs.flush();
    fs.close();
}


/*
 // Workflow creation
 // It's a pretty simple workflow that does absolutely nothing :)
 // Aside printing hello
 
 */