/*
 * =====================================================================================
 *
 *       Filename:  loop.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/14 02:44:51
 *       Revision:  none
 *       Compiler:  
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#include "loop.hpp"
#include "module.hpp"

void Loop::addEvent(std::list<Module*> &moduleList)
{
	std::list<Module*>::iterator it;
	Module *md;	
	for(it=moduleList.begin();it!=moduleList.end();it++){
		md=*it;
		eventList_.push_back(md);
	}

}

void Loop::eventLoop(unsigned long long step)
{
	while(1){
		step_++;
		fn_(step);

		//do method
		std::list<Module*>::iterator it;
		Module *md;	
		for(it=eventList_.begin();it!=eventList_.end();it++){
			md=*it;
			md->method();		
		}
		eventList_.clear();

		if(step_==step)
			break;
	}
}

