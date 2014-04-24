/*
 * =====================================================================================
 *
 *       Filename:  clkobject.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24/04/14 06:11:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#ifndef __clkobject_H__
#define __clkobject_H__
#include "rtlobject.hpp"
/*for simplify, just make a totally new class of clock*/

typedef boost::function<void()> clkCallback;
class ClkObject: public RtlObject{
  public:
	ClkObject(String name, int step):
		RtlObject(name),
		step_(step)
	{
	
	}
	~ClkObject(){}

	void setReset(RtlObjectPtr& reset,LevelType type ){
		reset_=reset;
		type_=type;	
	}
	
	void addPosLoad(clkCallback func){
		posLoadList_.push_back(func);
	}

	void update(int step){
		std::list<clkCallback>::iterator it;
		if(reset_->getVal()==type_){
			/*all reset is Async reset*/
			val_=0;
		}
		else if((step/step_)%2){
			//odd clock =1
			if(0==val_){
				val_=1;
				for(it=posLoadList_.begin();it!=posLoadList_.end();++it){
					(*it)();			
				}
			}

		}	
		else if(0==((step/step_)%2)){
			//even clock =1
			if(1==val_){
				val_=0;
				for( it=negLoadList_.begin();it!=negLoadList_.end();++it){
					(*it)();			
				}
			}

		}	

	}


  private:
	int step_;
	LevelType type_;
	RtlObjectPtr reset_;
	std::list<clkCallback> posLoadList_;
	std::list<clkCallback> negLoadList_;
};


#endif

