struct VertexInput
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float4 color : COLOR0;
};

cbuffer CameraBuffer : register(b0) // ->  0 ~ 13 // 4096 * 16byte
{
    matrix view;
    matrix proj;
};

cbuffer TransformBuffer : register(b1) // ->  0 ~ 13 // 4096 * 16byte
{
    matrix world;
};

cbuffer ColorBuffer : register(b2) // ->  0 ~ 13 // 4096 * 16byte
{
    float4 color;
};


PixelInput VS(VertexInput input)
{
    // 1 x 4            4 x 4  -----> 1 x 4
    //1, 2, 3, 1   *    0000
    //                  0000
    //                  0000
    //                  0000

    PixelInput output;
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);

    output.color = input.color;
 
    return output;
}

float4 PS(PixelInput input) : SV_Target
{
    // Pixel Shader�� ��ȯ�ϴ� ������ 1.0f�� �ִ밪�̴�.
    // ���� format�� DXGI_FORMAT_R8G8B8A8_UNORM 
    // + color�� �ϸ� 1.0f�� �Ѱܹ�����. Pixel Shader�� ��ȯ�ϴ� ������ 1.0f�� �ִ��̴�. �׷��� ������ �����ش�.
    // �׷��� *�� �ϸ� �ȴ�. ��� intersect_color = D3DXCOLOR(1, 1, 1, 1) �⺻���� �������Ѵ�.
    // 0, 0, 0, 0���� �ϸ� ���ϸ� �� 0�� �Ǽ� �������� ����
    // ���� �浹�ؼ� intersect_color�� 1.0f, 0.f, 0.f, 1.0f �� �Ǹ� ���ϸ� Ư������ ����� �ִ�.
    
    // return input.color * color;
    return input.color;
}