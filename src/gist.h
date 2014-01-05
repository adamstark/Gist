//=======================================================================
/** @file gist.h
 *  @brief Includes all relevant parts of the 'Gist' audio analysis library
 *  @author Adam Stark
 *  @copyright Copyright (C) 2013  Adam Stark
 *
 * This file is part of the 'Gist' audio analysis library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//=======================================================================


#ifndef __GISTHEADER__
#define __GISTHEADER__

#define GIST_VERSION "0.1.0"

// core
#include "core/CoreTimeDomainFeatures.h"
#include "core/CoreFrequencyDomainFeatures.h"

// onset detection functions
#include "onset-detection-functions/OnsetDetectionFunction.h"

// pitch detection
#include "pitch/Yin.h"



#endif
