/*++

Copyright (C) 2015 Microsoft Corporation (Original Author)
Copyright (C) 2015 netfabb GmbH

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Abstract:

NMR_ModelReaderNode100_Texture2D.cpp implements the Model Reader Texture2D Class.

--*/

#include "Model/Reader/v100/NMR_ModelReaderNode100_Texture2D.h"

#include "Model/Classes/NMR_ModelConstants.h"
#include "Model/Classes/NMR_ModelMeshObject.h"
#include "Model/Classes/NMR_ModelResource.h"
#include "Model/Classes/NMR_ModelTexture2D.h"
#include "Model/Classes/NMR_Model.h"

#include "Common/NMR_StringUtils.h"
#include "Common/NMR_Exception.h"
#include "Common/NMR_Exception_Windows.h"

namespace NMR {

	CModelReaderNode100_Texture2D::CModelReaderNode100_Texture2D(_In_ CModel * pModel, _In_ PModelReaderWarnings pWarnings)
		: CModelReaderNode(pWarnings)
	{
		// Initialize variables
		m_nID = 0;

		m_pModel = pModel;
	}

	void CModelReaderNode100_Texture2D::parseXML(_In_ CXmlReader * pXMLReader)
	{
		// Parse name
		parseName(pXMLReader);

		// Parse attribute
		parseAttributes(pXMLReader);

		// Use parameter and assign to model Object
		if (m_nID == 0)
			throw CNMRException(NMR_ERROR_MISSINGMODELRESOURCEID);

		// Create Resource
		m_pTexture2DResource = std::make_shared<CModelTexture2DResource> (m_nID, m_pModel);

		m_pModel->addResource(m_pTexture2DResource);

		// Set Properties
		m_pTexture2DResource->setPath(m_sPath);
		m_pTexture2DResource->setContentTypeString(m_sContentType, true);
		m_pTexture2DResource->setTileStyleU(m_sTileStyleU);
		m_pTexture2DResource->setTileStyleV(m_sTileStyleV);

		// Parse Content
		parseContent(pXMLReader);

	}

	void CModelReaderNode100_Texture2D::OnAttribute(_In_z_ const nfWChar * pAttributeName, _In_z_ const nfWChar * pAttributeValue)
	{
		__NMRASSERT(pAttributeName);
		__NMRASSERT(pAttributeValue);

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TEXTURE2D_ID) == 0) {
			if (m_nID != 0)
				throw CNMRException(NMR_ERROR_DUPLICATERESOURCEID);

			// Convert to integer and make a input and range check!
			m_nID = fnWStringToUint32(pAttributeValue);
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TEXTURE2D_PATH) == 0) {
			m_sPath = std::wstring(pAttributeValue);
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TEXTURE2D_CONTENTTYPE) == 0) {
			m_sContentType = std::wstring(pAttributeValue);
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TEXTURE2D_TILESTYLEU) == 0) {
			m_sTileStyleU = std::wstring(pAttributeValue);
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TEXTURE2D_TILESTYLEV) == 0) {
			m_sTileStyleV = std::wstring(pAttributeValue);
		}

	}


}
