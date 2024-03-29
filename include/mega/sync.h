/**
 * @file mega/sync.h
 * @brief Class for synchronizing local and remote trees
 *
 * (c) 2013-2014 by Mega Limited, Auckland, New Zealand
 *
 * This file is part of the MEGA SDK - Client Access Engine.
 *
 * Applications using the MEGA API must present a valid application key
 * and comply with the the rules set forth in the Terms of Service.
 *
 * The MEGA SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

#ifndef MEGA_SYNC_H
#define MEGA_SYNC_H 1

#include "megaclient.h"

namespace mega {
class MEGA_API Sync
{
public:
    MegaClient* client;

    // root of local filesystem tree, holding the sync's root folder
    LocalNode localroot;

    // current state
    syncstate_t state;

    // are we conducting a full tree scan? (during initialization and if event notification failed)
    bool fullscan;

    // deletion queue
    set<int32_t> deleteq;

    // insertion/update queue
    localnode_set insertq;

    // adds an entry to the delete queue - removes it from insertq
    void statecachedel(LocalNode*);

    // adds an entry to the insert queue - removes it from deleteq
    void statecacheadd(LocalNode*);

    // recursively add children
    void addstatecachechildren(uint32_t, idlocalnode_map*, string*, LocalNode*, int);
    
    // Caches all synchronized LocalNode
    void cachenodes();

    // change state, signal to application
    void changestate(syncstate_t);

    // sync-wide directory notification provider
    DirNotify* dirnotify;

    // process and remove one directory notification queue item from *notify
    dstime procscanq(int);

    // recursively look for vanished child nodes and delete them
    void deletemissing(LocalNode*);

    // scan specific path
    LocalNode* checkpath(LocalNode*, string*, string* = NULL);

    m_off_t localbytes;
    unsigned localnodes[2];

    // look up LocalNode relative to localroot
    LocalNode* localnodebypath(LocalNode*, string*, LocalNode** = NULL, string* = NULL);

    // scan items in specified path and add as children of the specified
    // LocalNode
    bool scan(string*, FileAccess*);

    // own position in session sync list
    sync_list::iterator sync_it;

    // rescan sequence number (incremented when a full rescan or a new
    // notification batch starts)
    int scanseqno;

    // notified nodes originating from this sync bear this tag
    int tag;

    // debris path component relative to the base path
    string debris, localdebris;

    // permanent lock on the debris/tmp folder
    FileAccess* tmpfa;

    // state cache table
    DbTable* statecachetable;

    // move file or folder to localdebris
    bool movetolocaldebris(string* localpath);

    // original filesystem fingerprint
    fsfp_t fsfp;
    
    Sync(MegaClient*, string*, const char*, string*, Node*, fsfp_t = 0, int = 0);
    ~Sync();

protected :
    bool readstatecache();

};
} // namespace

#endif
