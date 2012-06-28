// **********************************************************************
//
// Copyright (c) 2003-2011 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.4.2
//
// <auto-generated>
//
// Generated from file `Bomberloutre_map_item.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <Bomberloutre_map_item.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 304
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 2
#       error Ice patch level mismatch!
#   endif
#endif

void
BomberLoutreInterface::MapItem::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(i);
    __os->write(j);
    __os->write(destructible);
    __os->write(walkable);
}

void
BomberLoutreInterface::MapItem::__read(::IceInternal::BasicStream* __is)
{
    __is->read(i);
    __is->read(j);
    __is->read(destructible);
    __is->read(walkable);
}

void
BomberLoutreInterface::__writeMapItems(::IceInternal::BasicStream* __os, const ::BomberLoutreInterface::MapItem* begin, const ::BomberLoutreInterface::MapItem* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
BomberLoutreInterface::__readMapItems(::IceInternal::BasicStream* __is, ::BomberLoutreInterface::MapItems& v)
{
    ::Ice::Int sz;
    __is->readAndCheckSeqSize(10, sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}

void
BomberLoutreInterface::Bomb::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(i);
    __os->write(j);
    __os->write(power);
    __os->write(timer);
}

void
BomberLoutreInterface::Bomb::__read(::IceInternal::BasicStream* __is)
{
    __is->read(i);
    __is->read(j);
    __is->read(power);
    __is->read(timer);
}

void
BomberLoutreInterface::__writeBombs(::IceInternal::BasicStream* __os, const ::BomberLoutreInterface::Bomb* begin, const ::BomberLoutreInterface::Bomb* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
BomberLoutreInterface::__readBombs(::IceInternal::BasicStream* __is, ::BomberLoutreInterface::Bombs& v)
{
    ::Ice::Int sz;
    __is->readAndCheckSeqSize(16, sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}

void
BomberLoutreInterface::Bonus::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(i);
    __os->write(j);
    __os->write(bomb);
    __os->write(kick);
    __os->write(power);
    __os->write(speed);
}

void
BomberLoutreInterface::Bonus::__read(::IceInternal::BasicStream* __is)
{
    __is->read(i);
    __is->read(j);
    __is->read(bomb);
    __is->read(kick);
    __is->read(power);
    __is->read(speed);
}

void
BomberLoutreInterface::__writeBonuses(::IceInternal::BasicStream* __os, const ::BomberLoutreInterface::Bonus* begin, const ::BomberLoutreInterface::Bonus* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
BomberLoutreInterface::__readBonuses(::IceInternal::BasicStream* __is, ::BomberLoutreInterface::Bonuses& v)
{
    ::Ice::Int sz;
    __is->readAndCheckSeqSize(21, sz);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}