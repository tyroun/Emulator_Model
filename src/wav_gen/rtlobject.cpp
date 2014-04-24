/*
 * =====================================================================================
 *
 *       Filename:  rtlobject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/04/14 09:43:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#include "rtlobject.hpp"

RtlObject::RtlObject(String name){
		shortName_=name;
		pThis_ = RtlObjectPtr(this);
		isSensitive_=false;
}

//void RtlObject::update(void)
//{
//	cb_();
//}



