/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 06:22:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#ifndef __common_H__
#define __common_H__
#include <iostream>
#include <boost/shared_ptr.hpp>

typedef std::string String;

typedef enum {Neg,Pos} LevelType;

template <typename T> class RtlObject;
template <typename T>
struct RtlObjectPtr
{
	typedef boost::shared_ptr< RtlObject<T> > type;
};

#endif

