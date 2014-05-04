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
#include "loop.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/any.hpp>

typedef boost::function<void()> ObjCallback;

class Module;

template <typename T>
class RtlObject 
{ 
  public:
//	typedef boost::shared_ptr<RtlObject> RtlObjectPtr; 
	template <typename T1> friend class sc_port;

	RtlObject(std::string& name);
	virtual ~RtlObject(){}

	T getVal(){return val_;}
//	RtlObjectPtr getDrv(){
//		return pThis_;
//	}	

	void setSensitive(Module *md){
		isSensitive_=true;
		moduleList.push_back(md);
	}

	bool isSensitive(){
		return isSensitive_;
	}

//	void update(){
//		std::list<Module*>::iterator it;
//		for(it=moduleList.begin();it!=moduleList.end();++it){
//			(*it)->method();
//		}
//	}

	//Operator 	
//	RtlObjectPtr operator & (){
//		return pThis_;
//	}	
	
	//bool operator == (const RtlObject& obj){
	//	return val_==obj.getVal();
	//}
	//bool operator != (const RtlObject& obj){
	//	return val_!=obj.getVal();
	//}
  protected:
	T val_;
//	RtlObjectPtr pThis_;
	bool isSensitive_;	
//	RtlObjectPtr pDrv_;	
//	ObjCallback cb_;
	String shortName_;//signal name
	std::list<Module*> moduleList;
};




#endif

