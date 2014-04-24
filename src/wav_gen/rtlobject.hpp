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
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/any.hpp>
class RtlObject;
typedef boost::function<void()> ObjCallback;
typedef boost::shared_ptr<RtlObject> RtlObjectPtr;

template <typename T>
class RtlObject 
{ 
  public:
	RtlObject(std::string name);
	~RtlObject(){}
//	virtual void update(void);
//	void addLoad(ObjCallback cb){cb_=cb;}

	boost::shared_ptr<T> getVal(){return val_;}
	RtlObjectPtr getDrv(){
		return pThis_;
	}	

	void setSensitve(){
		isSensitive_=true;
	}

	//Operator 	
	virtual T operator=(T val){
		if(val_!=val){
			val_=val;
			Loop::getInstance()->sendEvent(pThis);
		}
	}

	virtual void operator=(RtlObjectPtr& p){
	//	pDrv_=p;
		if(val_!=p->getVal()){
			val_=p->getVal();
			Loop::getInstance()->sendEvent(pThis);
		}

	}

	RtlObjectPtr operator & (){
		return pThis_;
	}	
	bool operator == (const RtlObject& obj){
		return val_==obj.getVal();
	}
	bool operator != (const RtlObject& obj){
		return val_!=obj.getVal();
	}
  protected:
	T val_;
	RtlObjectPtr pThis_;	
//	RtlObjectPtr pDrv_;	
//	ObjCallback cb_;
	String shortName_;//signal name
	bool isSensitive_;
};






#endif

