#version 410

uniform vec3 lightPos;
uniform float lightRadius;
uniform vec3 lightCol;
uniform vec3 ambientCol;
uniform vec3 camPos;
uniform sampler2D normalTex;
uniform sampler2D diffuseTex;
uniform sampler2D specularTex;

in mat3 TBN;
in vec2 fragUV;
in vec3 fragWorldPos;
out vec4 outCol;

float diffuse(vec3 lightDir, vec3 nrm){
    float diffAmt=max(0,dot(lightDir,nrm));
    return diffAmt;
}

float specular(vec3 lightDir, vec3 viewDir, vec3 nrm, float shinness){
    vec3 halfVec = lightDir+viewDir;
    float specAmt = max(0,dot(halfVec,nrm));
    specAmt = pow(specAmt,shinness);
    return specAmt;
}

void main(){
    vec3 nrm = texture(normalTex,fragUV).rgb;
    nrm = normalize(nrm*2-1);
    nrm=normalize(TBN*nrm);

    vec3 tolight=lightPos-fragWorldPos;
    vec3 lightDir=normalize(tolight);
    float dist = length(tolight);
    float falloff = max(0,1-dist/lightRadius);
    vec3 viewDir=normalize(camPos-fragWorldPos);
    
    float diffAmt = diffuse(lightDir,nrm);
    vec3 diffCol=texture(diffuseTex,fragUV).rgb;
    diffCol=diffCol*lightCol*falloff*diffAmt;

    float specAmt = specular(lightDir,viewDir,nrm,4);
    float specTex=texture(specularTex,fragUV).r;
    vec3 specCol=specTex*lightCol*falloff*specAmt;

    outCol=vec4(diffCol+specCol,1);
}