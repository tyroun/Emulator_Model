/*
 * =====================================================================================
 *
 *       Filename:  rtlobject.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 05:41:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#ifndef __rtlobject_H__
#define __rtlobject_H__
#include "common.h"
#include <list>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/any.hpp>

typedef boost::function<void()> ObjCallback;

class RtlObject: public boost::noncopyable 
{ 
  public:
	RtlObject(String& name){
		shortName_=name;
	}
	~RtlObject(){
	}

	virtual void update(void);
	
	void addLoad(ObjCallback cb){cb_=cb;}

	bool getVal(){return val_;}
	
	virtual bool operator=(bool val);
  protected:
	bool val_;	
	ObjCallback cb_;
	String shortName_;//signal name
};

typedef boost::shared_ptr<RtlObject> RtlObjectPtr;



/*for simplify, just make a totally new class of clock*/
class ClkObject: public RtlObject{
  public:
	ClkObject(String &name, int step):
		RtlObject(name),
		step_(step)
	{
	
	}
	~ClkObject();

	void setReset(RtlObjectPtr reset,LevelType &type ){
		reset_=reset;
		type_=type;	
	}

	void update(int step){
		std::list<RtlObjectPtr>::iterator it;
		if(reset_->getVal()==type_){
			/*all reset is Async reset*/
			val_=0;
		}
		else if((step/step_)%2){
			//odd clock =1
			if(0==val_){
				val_=1;
				for(it=posLoadList_.begin();it!=posLoadList_.end();++it){
					it->update();			
				}
			}

		}	
		else if(0==((step/step_)%2)){
			//even clock =1
			if(1==val_){
				val_=0;
				for( it=negLoadList_.begin();it!=negLoadList_.end();++it){
					it->update();			
				}
			}

		}	

	}


  private:
	int step_;
	LevelType type_;
	RtlObjectPtr reset_;
	std::list<RtlObjectPtr> posLoadList_;
	std::list<RtlObjectPtr> negLoadList_;
};


#endif

