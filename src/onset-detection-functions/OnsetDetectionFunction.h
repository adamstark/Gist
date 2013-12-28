//=======================================================================
/** @file OnsetDetectionFunction.h
 *  @brief Implementations of onset detection functions
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


#ifndef __ONSETDETECTIONFUNCTION__
#define __ONSETDETECTIONFUNCTION__

#include <vector>

template <class T>
class OnsetDetectionFunction
{
    
public:
    /** constructor */
    OnsetDetectionFunction(int frameSize);
    
    /** Sets the frame size of internal buffers. Assumes all magnitude
     * spectra are passed as the first half (i.e. not mirrored)
     * @param frameSize the frame size
     */
    void setFrameSize(int frameSize);
    
    
    T spectralDifference(std::vector<T> magnitudeSpectrum);
    
    T spectralDifferenceHWR(std::vector<T> magnitudeSpectrum);
    
private:
    
    std::vector<T> prevMagnitudeSpectrum;
    
};

#endif