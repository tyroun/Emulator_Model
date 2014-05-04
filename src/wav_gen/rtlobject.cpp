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

template <typename T>
RtlObject<T>::RtlObject(std::string& name){
		shortName_=name;
		isSensitive_=false;
}

template RtlObject<bool>;

//void RtlObject::update(void)
//{
//	cb_();
//}



