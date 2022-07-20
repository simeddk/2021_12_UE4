#include "stdafx.h"
#include "VertexLine2Demo.h"

void VertexLine2Demo::Initialize()
{
	shader = new Shader(L"03_Pass.fxo");

	vertices[0].Position = Vector3(0, 0, 0);
	vertices[1].Position = Vector3(1, 0, 0);

	vertices[2].Position = Vector3(0, 0.5f, 0);
	vertices[3].Position = Vector3(1, 0.5f, 0);

	vertices[4].Position = Vector3(0, -0.5f, 0);
	vertices[5].Position = Vector3(1, -0.5f, 0);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 6;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
}

void VertexLine2Demo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void VertexLine2Demo::Update()
{
	
}

void VertexLine2Demo::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//Topology Test
	{
		static bool bLineStrip = false;
		ImGui::Checkbox("LineStrip", &bLineStrip);

		D3D11_PRIMITIVE_TOPOLOGY topologies[2] =
		{
			D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
			D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
		};

		D3D::GetDC()->IASetPrimitiveTopology(bLineStrip ? topologies[1] : topologies[0]);
	}

	//Pass Test
	static UINT pass = 0;
	{
		ImGui::InputInt("Pass", (int*)&pass);
		pass = Math::Clamp<UINT>(pass, 0, 3);

		static Color color = Color(1, 1, 1, 1);
		ImGui::ColorEdit3("Line Color", color);
		shader->AsVector("Color")->SetFloatVector(color);
	}

	//StartLocation Test
	static UINT startLocation = 0;
	{
		ImGui::SliderInt("Start Location", (int*)&startLocation, 0, 6);
	}

	shader->Draw(0, pass, 6, startLocation);
}
