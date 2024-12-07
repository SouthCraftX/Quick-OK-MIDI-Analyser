#pragma once
#define __QOMA_BASE_H__

#include "xoceanlib/include/base.h"


enum QOMA_SpecificError
{
    QOMA_TRACK_LENGTH_MISMATCH = 5000,
    QOMA_BAD_TRACK,
};

// Describe whether the argument is in or out.
#define _QOMA_IN_
#define _QOMA_OUT_
#define _QOMA_INOUT_

