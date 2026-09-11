#ifndef VEC3_H
#define VEC3_H

#include "rtproject.h"

using namespace std;

class vec3 {
    public:
        double e[3];

        vec3() : e{0, 0, 0} {} // Sem definir valores na criação
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} // Se definir valores na criação

        // Função para retornar os valores xyz
        // Const serve para informar ao compilador que chamar essas funções não modifica nenhum dado do vetor
        double x() const { return e[0]; };
        double y() const { return e[1]; };
        double z() const { return e[2]; };
        
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // Invertes valores
        double operator[](int i) const { return e[i]; } // Só leitura
        double& operator[](int i) { return e[i]; } // Permite alteração

        vec3& operator+=(const vec3& v) { // Só pra somar vetores, você vai pegar o vetor atual e somar com o vetor que colocar ali
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this; 
        }
        

        vec3& operator*=(double t) { // Só pra multiplicar valores de um vetor, a partir de um valor determinado,
                                     // Você vai pegar o vetor atual e multiplicar todos os elementos, pelo valor recebido
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
        }

        vec3& operator/=(double t) { 
            return *this *= 1/t;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        // Pitágoras em 3D, basicamente A² + B² + C² = D²]
};

using point3 = vec3; 

// Vector Utility Functions (VUF)
/*
Esta função serve para você conseguir imprimir o vetor direto na tela usando std::cout (ou salvar em arquivo com std::ofstream), como se ele fosse um tipo nativo do C++.
Em vez de escrever:
std::cout << v.x() << ' ' << v.y() << ' ' << v.z();
Você passa a poder escrever simplesmente:
std::cout << v << '\n';
*/
/*
inline
Sugere ao compilador que insira o código desta função diretamente no local onde ela for chamada, 
em vez de fazer uma chamada de função tradicional. 
Isso é usado para ganho de performance em funções pequenas e frequentemente chamadas, 
além de evitar erros de "definição duplicada" (linkage) se este arquivo de cabeçalho (.h) for incluído em múltiplos lugares.
*/

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
} 

// Operações semelhantes as criadas na classe vec3
// Soma e subtraem os vetores
inline vec3 operator+(const vec3& u, const vec3& v){
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v){
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// ao inves de fzr v[0] + u[0]... só fzr v + u

inline vec3 operator*(const vec3& u, const vec3& v){
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Serve para fazer tanto v * t, tanto t * v
inline vec3 operator*(double t, const vec3& v){
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vec3 operator*(const vec3& v, double t){
    return t * v;
}

inline vec3 operator/(const vec3& v, double t){
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v){ // pegar o angulo dos dois pontos
    return u.e[0] * v.e[0]
        +  u.e[1] * v.e[1]
        +  u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

//
//     .-----
//           ------.
//

#endif