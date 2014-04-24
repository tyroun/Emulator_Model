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

class RtlObject 
{ 
  public:
	RtlObject(std::string name);
	~RtlObject(){}
	virtual void update(void);
	void addLoad(ObjCallback cb){cb_=cb;}

	bool getVal(){return val_;}
	
	virtual bool operator=(bool val);
	virtual void operator=(RtlObjectPtr& p){
		val_=p->getVal();
	}

  protected:
	bool val_;	
	ObjCallback cb_;
	String shortName_;//signal name
};






#endif

