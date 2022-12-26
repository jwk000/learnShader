#version 410

uniform vec3 camPos;
uniform vec3 lightDir;//单位向量，光线方向取反
uniform vec3 lightCol;
uniform vec3 meshCol;
uniform vec3 ambientCol;

in vec3 fragNrm;
in vec3 fragWorldPos;

out vec4 outCol;

void main(){
    vec3 nrm = normalize(fragNrm);
    vec3 viewDir = normalize(camPos-fragWorldPos);
    //phong模型计算高光
    vec3 refDir = reflect(-lightDir, nrm);
    float specAmt = max(0,dot(refDir,viewDir));
    //blinn-phong模型计算高光
    vec3 halfVec = normalize(viewDir+lightDir);
    specAmt = max(0,dot(halfVec,nrm));
    
    specAmt = pow(specAmt,20);
    vec3 specCol=lightCol*meshCol*specAmt;

    float diffAmt = max(0,dot(nrm,lightDir));
    vec3 diffCol = lightCol*meshCol*diffAmt;

    vec3 amCol= ambientCol* meshCol;
    outCol = vec4(diffCol+specCol+amCol,1);
}