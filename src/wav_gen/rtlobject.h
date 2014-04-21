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
#include <map>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
//#include <boost/any.hpp>

class RtlObject :  public boost::noncopyable{
  public:
	RtlObject(String& name){
		shortName_=name;
				
	}
	~RtlObject(){
	}

	typedef boost::function<void()> ObjCallback;

	void update(){cb_();}
	
	void addLoad(ObjCallback cb){cb_=cb;}

	bool getVal(){return val_;}
	
	virtual bool operator=(bool val){val_=val;}
	virtual	bool operator=(RtlObject &obj){val_=obj->getVal;}
	
  private:
	std::list<RtlObject*> loadList_;
	bool val_;	
	ObjCallback cb_;
	String shortName_;//signal name
};
typedef boost::shared_ptr<RtlObject> RtlObjectPtr;

/*for simplify, just make a totally new class of clock*/
class ClkObject{
  public:
	ClkObject(String &name, int step):
		step_(step),
		name_(name)
	{
	
	}
	~ClkObject();

	void setReset(RtlObject* reset,LevelType &type ){
		reset_=reset;
		type_=type;	
	}

	void update(int step){
		RtlObject *obj;
		if(reset_->getVal()==type_){
			/*all reset is Async reset*/
			val_=0;
		}
		else if((step/step_)%2){
			//odd clock =1
			if(0==val_){
				val_=1;
				for(posLoadList_::iterator it=posLoadList_.begin();it!=posLoadList_.end();++it){
					obj=it.value();
					obj->update();			
				}
			}

		}	
		else if(0==((step/step_)%2)){
			//even clock =1
			if(1==val_){
				val_=0;
				for(negLoadList_::iterator it=negLoadList_.begin();it!=negLoadList_.end();++it){
					obj=it.value();
					obj->update();			
				}
			}

		}	

	}


  private:
	int step_;
	LevelType type_;
	RtlObject *reset_;
	std::list<RtlObject*> posLoadList_;
	std::list<RtlObject*> negLoadList_;
	unsigned char val_;
	String name_;
};


#endif

