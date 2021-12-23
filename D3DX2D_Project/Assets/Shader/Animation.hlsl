// VertexInput�� InputLayout(IA �ܰ�) Ÿ���� �ٸ��� ������ ����.
struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
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

// keyframe ������ �޾ƿ��� ���� constantbuffer�� �����.
cbuffer AnimationBuffer : register(b2)
{
    float2 sprite_offset; //keyframe�� ������ �ִ� offset
    float2 sprite_size; //keyframe�� ������ �ִ� size 
    float2 texture_size; //�ؽ����� ���� ũ��
    float is_animated; // �ִϸ��̼��� ������ �ִ���
    float padding;
    float4 color_key;
}

PixelInput VS(VertexInput input)
{
    // 1 x 4            4 x 4  -----> 1 x 4
    //1, 2, 3, 1   *    0000
    //                  0000
    //                  0000
    //                  0000

    /*
        �츮�� ���⼭ ��������Ʈ�̹���(��Ʋ��) 1���� �ް�
        Ư�� �κи� ������ ����� ���̴�.(UV��)
    
        UV�� �����ؾ���
    */
    PixelInput output;
    
    // �̰� �ϴ� ������.. ���� �����ÿ� ���� ����� �� �ʿ䰡 ����. �׷��� �ָ� �ᱹ �̹����� ©���� �����Ǽ� ���´�.
    // �̹����� �� ũ�Ⱑ �ٸ���. �׷��� �̹��� ����� ũ��� �����. �̹��� ũ���� ��µ� �� �ֵ���
    // ������ �̷��� ������, hlsl���� �̷��� �� �ʿ䰡 ����.
    //output.position = float4(input.position.x * sprite_size.x, input.position.y * sprite_size.y, 0.0f, 1.0f)
    //hlsl������ float4�� �����͵� �����ϰ� float3, float2, float���·� �ٲ� ����� �� �ִ�.
    // �̷��� ���� float 2���� ���ϱⰡ �����ϴ�.
    // ���� ���� ����
    // input.xxxx �� ����...
    // �̷��� �����ָ� �� ũ�⸸ŭ ���� ������ �ȴ�.
    // ���� ������ �־ ������ shader�� �и��ϴ� ���� ����.(�����̳��ϸ��� �ؽ��Ŀ� shader�� �ִϸ��̼ǿ� shader �÷��� shader�� �����ؼ�
    // Meshrenderer������ shader�� ��θ� �Ķ���ͷ� �޾� �ܺο��� ó���ϴ� ���� ����.)
    output.position = float4(input.position.xy * sprite_size, 0.0f, 1.0f);
    
    output.position = mul(output.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);

    // 0 ~ 1�� uv ��ǥ�� ����
    output.uv = input.uv;
    // ���� ũ���� �÷���
    output.uv *= sprite_size / texture_size; // ����ȭ�� ũ�Ⱑ ����(�Ҽ��� ������) ex ) 200 / 1000 = 0.2 �̰� ���� ũ�⿡ * 0.2 ���ָ� �� ũ�⸸ŭ �ȴ�.
    // Ư�� �����¸�ŭ �̵�
    output.uv += sprite_offset / texture_size;

    return output;
}

Texture2D source_texture : register(t0);
SamplerState samp        : register(s0); //16 -> 0 ~ 15

float4 PS(PixelInput input) : SV_Target
{
    if(is_animated)
    {
        float4 color = 0.0f;

        color = source_texture.Sample(samp, input.uv);
        
        if (any(color_key))
        {
            float4 color_key_normal = color_key / 255;
            if (abs(color_key_normal.r - color.r) < 0.01)
                   discard;
            
            return color;
        }
        
        else
            return color;
    }
    
    // Shader�� �۵��ϰ� �ִ��� Ȯ���ϰ� ���� ��� Ư�� ���� �������� �ڵ帣 �ۼ��ϰ�
    // ������� Ȯ���Ѵ�. - visualstudio�� GPU profiling ����� ����ص� ����.
    else
        return float4(1, 0, 0, 1);
}