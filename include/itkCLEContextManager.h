/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef itkCLEContextManager_h
#define itkCLEContextManager_h

#include "itkLightObject.h"
#include "CLEsperantoExport.h"

#include "clesperanto.hpp"

namespace itk
{
/** \class CLEContextManager
 *
 * \brief Class to store the CLE context.
 *
 *  Write more documentation here...
 *
 * \ingroup CLEsperanto
 */
class CLEsperanto_EXPORT CLEContextManager : public LightObject
{
public:
  static cle::Clesperanto &
  GetInstance()
  {
    return m_CLE;
  }

private:
  static cle::Clesperanto m_CLE;
};
} // namespace itk

#endif
