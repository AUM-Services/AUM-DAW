//Written by Eric Dee.

#include "AUM-Ono-API-Graphics-Index-Buffer.h"

namespace AUM_Ono_API_Graphics {

	AUMOnoAPIGraphicsIndexBuffer::AUMOnoAPIGraphicsIndexBuffer() {
		this->typeCount = 0;
		this->indiciesBufferId = 0;
	}

	AUMOnoAPIGraphicsIndexBuffer::AUMOnoAPIGraphicsIndexBuffer
		(unsigned int typeCount, const unsigned int* phaseIndicies)
	{
		this->typeCount = typeCount;
		glGenBuffers(1, &this->indiciesBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indiciesBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) *typeCount, phaseIndicies, GL_STATIC_DRAW);
	}

	void AUMOnoAPIGraphicsIndexBuffer::Bind
		()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indiciesBufferId);
	}

	void AUMOnoAPIGraphicsIndexBuffer::Unbind
		() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int AUMOnoAPIGraphicsIndexBuffer::GetCount
		()
	{
		return this->typeCount;
	}

	unsigned int* AUMOnoAPIGraphicsIndexBuffer::GetAddress
	()
	{
		return &this->indiciesBufferId;
	}

}