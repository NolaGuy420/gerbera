/*  ref.h - this file is part of MediaTomb.
                                                                                
    Copyright (C) 2005 Gena Batyan <bgeradz@deadlock.dhs.org>,
                       Sergey Bostandzhyan <jin@deadlock.dhs.org>
                                                                                
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
                                                                                
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
                                                                                
    You should have received a copy of the GNU General Public License
    along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __HASH_DBB_HASH_H__
#define __HASH_DBB_HASH_H__

#include "direct_hash_base.h"

template <typename KT, typename VT> struct dbb_hash_slot
{
    KT key;
    VT value;
};

template <typename KT, typename VT>
class DBBHash : public DHashBase<KT, struct dbb_hash_slot<KT, VT> >
{
protected:
    KT emptyKey;
public:
    DBBHash(int capacity, KT emptyKey) : DHashBase<KT, struct dbb_hash_slot<KT, VT> >(capacity)
    {
        this->emptyKey = emptyKey;
        clear();
    }

    /* virtual methods */
    virtual int hashCode(KT key)
    {
        return baseTypeHashCode((unsigned int)key);
    }
    virtual bool match(KT key, struct dbb_hash_slot<KT, VT> *slot)
    {
        return (key == slot->key);
    }
    virtual bool isEmptySlot(struct dbb_hash_slot<KT, VT> *slot)
    {
        return (slot->key == emptyKey);
    }

    void clear()
    {
        if (! emptyKey)
            zero();
        else
        {
            for (int i = 0; i < capacity; i++)
                data[i].key = emptyKey;
            count = 0;
        }
    }
   
    inline void put(KT key, VT value)
    {
        struct dbb_hash_slot<KT, VT> *slot;
        bool found = search(key, &slot);
        if (! found)
        {
            slot->key = key;
            count++;
        }
        slot->value = value;
    }
    inline void put(KT key, hash_slot_t destSlot, VT value)
    {
        struct dbb_hash_slot<KT, VT> *slot = (struct dbb_hash_slot<KT, VT> *)destSlot;
        if (slot->key == emptyKey)
        {
            slot->key = key;
            count++;
        }
        slot->value = value;
    }

    inline bool get(KT key, VT *value)
    {
        struct dbb_hash_slot<KT, VT> *slot;
        bool found = search(key, &slot);
        if (found)
            *value = slot->value;
        return found;
    }
    bool get(KT key, hash_slot_t *destSlot, VT *value)
    {
        struct dbb_hash_slot<KT, VT> **slot = (struct dbb_hash_slot<KT, VT> **)destSlot;
        bool found = search(key, slot);
        if (found)
            *value = (*slot)->value;
        return found;
    }
    inline bool exists(KT key)
    {
        struct dbb_hash_slot<KT, VT> *slot;
        return search(key, &slot);
    }
    inline bool exists(KT key, hash_slot_t *destSlot)
    {
        return search(key, (struct dbb_hash_slot<KT, VT> **)destSlot);
    }
};

#endif // __HASH_DBB_HASH_H__

