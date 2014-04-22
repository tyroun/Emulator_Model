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
#include "rtlobject.h"

void RtlObject::update(void)
{
	cb_();
}

bool RtlObject::operator=(bool val)
{
	val_=val;
}

