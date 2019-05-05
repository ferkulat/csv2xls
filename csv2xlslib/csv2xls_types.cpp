//
// Created by marcel on 4/28/19.
//

#include "csv2xls_types.h"
namespace csv2xls
{
bool operator<(OutPutRowLimit v1, OutPutRowLimit v2)
{
    return v1.Get() < v2.Get();
}

}

