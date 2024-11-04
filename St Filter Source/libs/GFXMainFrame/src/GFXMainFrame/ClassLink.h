#pragma once

// Hello Linux kernel
// https://github.com/torvalds/linux/blob/master/include/linux/list.h#L600

// This code is probably a product of:
// DEV: 여전히 충돌하고 있습니다. 어떻게해야합니까?
// BOSS: 문제를 해결하거나 해고하십시오!
#include <remodel/GlobalVar.h>

#define CLASSLINK_LOOP_BEGIN(cls) \
        for (CClassLink<cls>::head.cursor = CClassLink<cls>::head.begin; CClassLink<cls>::head.cursor != 0; /* no auto increment */) { \
        cls *obj = CClassLink<cls>::head.cursor->container();


#define CLASSLINK_LOOP_END(cls)                                                     \
        if (CClassLink<cls>::head.cursorInvalidated) {                              \
            CClassLink<cls>::head.cursorInvalidated = false;                        \
        } else {                                                                    \
            CClassLink<cls>::head.cursor = CClassLink<cls>::head.cursor->next;      \
        }                                                                           \
    }

#define CLASSLINK_STATIC_IMPL2(cls) \
    template<> bool CClassLink<CICharactor>::doLink; \
    template<> int CClassLink<cls>::count; \
    template<> CClassLink<cls> *CClassLink<cls>::begin; \
    template<> CClassLink<cls> *CClassLink<cls>::end; \
    template<> CClassLink<cls> *CClassLink<cls>::cursor; \
    template<> bool CClassLink<cls>::cursorInvalidated;


#define CLASSLINK_STATIC_IMPL(cls) \
    template<> CClassLink<cls>::SClassLinkListHead CClassLink<cls>::head(GFX_RUNTIME_CLASS(cls));

template<typename T>
class CClassLink {
    // TODO: Once all ClassLink references are resolved, we need to remove
    //       that structure and use the members directly
    struct SClassLinkListHead {

        explicit SClassLinkListHead(const CGfxRuntimeClass *cls) :
                runtimeClass(cls),
                doLink(true),
                count(0),
                begin(NULL), end(NULL), cursor(NULL),
                cursorInvalidated(0) {

        }

        const CGfxRuntimeClass *runtimeClass;
        bool doLink;
        int count;
        CClassLink<T> *begin;
        CClassLink<T> *end;
        CClassLink<T> *cursor;
        int cursorInvalidated;
    };
public:
    CClassLink()
            : isLinked(false), prev(0), next(0) {
        if (!head.doLink)
            return;

        isLinked = true;

        // Are we first?
        if (head.begin == NULL) {
            head.begin = this;
            head.end = this;
        } else {
            head.end->next = this;
            this->prev = head.end;
            this->next = NULL;
            head.end = this;
        }
        head.count++;
    }

    virtual ~CClassLink() {
        if (!isLinked)
            return;

        isLinked = false;
        if (head.cursor == this) {
            head.cursor = this->next;
            head.cursorInvalidated = true;
        }

        head.count--;

        // Replace list begin if we are first entry
        if (prev == 0) {
            head.begin = this->next;
        } else {
            prev->next = next;
        }

        // If we have a next, update that one
        if (next != 0) {
            next->prev = prev;
        } else {
            head.end = prev;
        }

        // We are gone now
        next = 0;
        prev = 0;
    }

    // get the container of this list head
    T *container() {
        return reinterpret_cast<T *>(reinterpret_cast<char*>(this) - offsetof(T, classLink));
    }

public: /* statics */
    static SClassLinkListHead head;

public: /* members */
    bool isLinked;
    CClassLink<T> *prev;
    CClassLink<T> *next;
};