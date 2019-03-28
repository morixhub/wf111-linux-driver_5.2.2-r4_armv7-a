/*****************************************************************************

            (c) Cambridge Silicon Radio Limited 2010
            All rights reserved and confidential information of CSR

            Refer to LICENSE.txt included with this source for details
            on the license terms.

*****************************************************************************/

#include <linux/kernel.h>
#include <linux/version.h>


#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 33)
#include <linux/autoconf.h>
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 16)
#include <linux/config.h>
#endif

#include <linux/slab.h>

#include "csr_panic.h"
#include "csr_pmem.h"

//[AESYS]
#include "linux/vmalloc.h"
#include "linux/random.h"

void *CsrPmemAlloc(CsrSize size)
{
    void *ret;

    ret = kmalloc(size, GFP_KERNEL);
    if (!ret)
    {
        CsrPanic(CSR_TECH_FW, CSR_PANIC_FW_HEAP_EXHAUSTION,
            "out of memory");
    }

    return ret;
}

void CsrPmemFree(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    kfree(ptr);
}

// [AESYS]
void *CsrPmemAllocVirtual(CsrSize size)
{
    void *ret = NULL;

    /* //!!
    // Sometimes simulate an allocation failure
    char c;
    get_random_bytes(&c, 1);

    if(c % 3 == 0)
        return(ret);
    */

    ret = vmalloc(size);

    return(ret);
}

// [AESYS]
void CsrPmemFreeVirtual(void *ptr)
{
    if(!ptr)
        return;

    vfree(ptr);
}
