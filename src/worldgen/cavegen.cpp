/*
   Copyright (c) 2011, The Mineserver Project
   All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>

#ifdef DEBIAN
#include <libnoise/noise.h>
#else
#include <noise/noise.h>
#endif

#include "../logger.h"
#include "../constants.h"
#include "../tools.h"
#include "../map.h"
#include "../config.h"
#include "../mineserver.h"

#include "cavegen.h"

void CaveGen::init(int seed)
{
  addCaveLava = Mineserver::get()->config()->bData("mapgen.caves.lava");
  caveSize = Mineserver::get()->config()->iData("mapgen.caves.size");
  caveTreshold = Mineserver::get()->config()->dData("mapgen.caves.treshold");
  
  // Set up us the Perlin-noise module.
  caveNoise.SetSeed(seed+1);
  caveNoise.SetFrequency(1.0/caveSize); // 1/20
  caveNoise.SetOctaveCount(2);
}

void CaveGen::AddCaves(uint8_t &block, int x, int y, int z)
{ 
  if(caveNoise.GetValue(x,y,z) < caveTreshold)
  {
    if(y < 10 && addCaveLava)
    {
      block = BLOCK_LAVA;
    }
    else
    {    
      block = BLOCK_AIR;
    }
  } 
}
