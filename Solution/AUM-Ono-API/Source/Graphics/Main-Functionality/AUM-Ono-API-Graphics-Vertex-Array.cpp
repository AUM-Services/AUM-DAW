//Written by Eric Dee.

#include "AUM-Ono-API-Graphics-Vertex-Array.h"

namespace AUM_Ono_API_Graphics {

	AUMOnoAPIGraphicsVertexArray::AUMOnoAPIGraphicsVertexArray
		()
	{
		this->Name = "Default Vertex Array";
		_TestGL_(glGenVertexArrays(1, &this->rendererId));
		if (_Graphics.Catch.ValidateAndReset())
		{
			AUMWorkstationItemCritical("OpenGL failed to instantiate a VAO in {0}.", this->Name);
			// Needs more enums.
			throw _Graphics.Catch.Errors.GLFW;
		}
	}

	AUMOnoAPIGraphicsVertexArray::~AUMOnoAPIGraphicsVertexArray
		()
	{
		// glDeleteVertexArrays(1, &this->rendererId);
	}

	void AUMOnoAPIGraphicsVertexArray::AddToBuffer
		(
			const AUMOnoAPIGraphicsVertexBuffer& vertexBuffer,
			const AUMOnoAPIGraphicsVertexBufferLayout& vertexBufferlayout
		)
	{
		this->Bind();
		vertexBuffer.Bind();
		const auto& elements = vertexBufferlayout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto &element = elements[i];
			/// <summary>
			/// Make this into a context gl helper method that takes WorkItems for their base values.
			/// </summary>
			/// <param name="vertexBuffer"></param>
			/// <param name="vertexBufferlayout"></param>
			_TestGL_(glEnableVertexAttribArray(i));
			if (_Graphics.Catch.ValidateAndReset())
			{
				AUMWorkstationError(
					"glEnableVertexAttribArray failed in {0} on index {1}.",
					this->Name,
					i
				);
			}
		
			/* Says to use the vao information bound to the vertex array as first arg
			with the buffer as second arg. */
			glVertexAttribPointer(
				i,
				element.Count_,
				element.Type_,
				element.GLNormalized_,
				vertexBufferlayout.GetStride(),
				(const void*)offset
			);
			
			offset += AUMOnoAPIGraphicsVertexBufferElement::GetSizeOfType(element.Type_) *element.Count_;
		}
	}

	void AUMOnoAPIGraphicsVertexArray::Bind
		() const
	{
		glBindVertexArray(rendererId);
	}

	void AUMOnoAPIGraphicsVertexArray::Unbind
		() const
	{
		glBindVertexArray(0);
	}

}