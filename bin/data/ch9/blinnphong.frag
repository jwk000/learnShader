#version 410

uniform vec3 camPos;
uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 ambientCol;
uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;

//in vec3 fragNrm;
in vec3 fragWorldPos;
in vec2 fragUV;
in mat3 TBN;

out vec4 fragCol;

void main(){
    //vec3 normal = normalize(fragNrm);
    //法线贴图
    vec3 nrm = texture(normalTex,fragUV).xyz;
    nrm=normalize(nrm*2-1);//切线空间的法线
    vec3 normal=normalize(TBN*nrm);//切线空间-世界空间
    
    vec3 viewDir = normalize(camPos-fragWorldPos);
    vec3 halfVec = normalize(viewDir+lightDir);
    float specAmt = max(0,dot(normal,halfVec));
    specAmt=pow(specAmt,4);

    float diffAmt=max(0,dot(normal,lightDir));
    vec3 meshCol = texture(diffuseTex,fragUV).xyz;
    vec3 diffCol=meshCol*lightCol*diffAmt;
    vec3 specCol=lightCol*texture(specularTex,fragUV).x*specAmt;
    vec3 ambiCol=meshCol*ambientCol;
    fragCol=vec4(specCol+diffCol+ambiCol,1);
}