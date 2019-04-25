//
// Created by marcel on 4/28/19.
//

#include "csv2xls_types.h"

bool operator<(OutPutRowLimit v1, OutPutRowLimit v2){
    return v1.Get() < v2.Get();
}

bool operator<(OutPutFileNameDigitCount v1, OutPutFileNameDigitCount v2){
    return v1.Get() < v2.Get();
}


