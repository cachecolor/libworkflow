#ifndef __PUT_DEFINITION_H_
#define __PUT_DEFINITION_H_
#include <string>
#include <tools/jsonable.h>
#include <tools/defines.h>

#pragma GCC visibility push(default)

SHARED_PTR(TypeChecker);

/**
    PutDefinition will describe actions inputs and outputs.
 */
struct PutDefinition : public Jsonable {
    PutDefinition();
    virtual ~PutDefinition();
    //! that's how it'll be defined / accessed.
    std::string put_name;
    //! This is purely meta information
    std::string description;
    //! Used by actions to check if what has been provided meet the requirements.
    TypeCheckerPtr checker;
    //! Tell whether this put is mandatory (ahah)
    //! Note: if it can live without it, but still provided, it still need to meet TypeChecker requirement. Default true
    bool mandatory ;
    //! If provided input is a list, and this is set to true, then, action WONT be executed.
    //! This is an input only property. default false
    bool ignoreEmpty ;
    //! if set to true, won't raise error if input is "Skiped" @sa StateMachine
    // Note, this is an Output only property. default false;
    bool allowSkip;
    
    bool operator<(const PutDefinition & ) const;
    
    void save(boost::property_tree::ptree & root) const override;
    void load(const boost::property_tree::ptree & root) override; 
};

#pragma GCC visibility pop

#endif // __PUT_DEFINITION_H_