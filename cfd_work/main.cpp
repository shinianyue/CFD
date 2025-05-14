#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

const int NX = 41;       // 网格X）
const int NY = 41;       // 网格Y
const int NSTEPS = 11000;  // 时间步
const double dt = 0.0005;  // 时间步长
const double dx = 1.0 / (NX - 1);
const double dy = 1.0 / (NY - 1);
const double nu = 0.1;   // 动力粘度系数

using Matrix = std::vector<std::vector<double>>;

Matrix zeros(int nx, int ny) {
    return Matrix(nx, std::vector<double>(ny, 0.0));
}

void write_csv(const Matrix& u, const Matrix& v, const std::string& filename) {
    std::ofstream file(filename);
    file << "x,y,u,v\n";
    for (int i = 0; i < NX; ++i) {
        for (int j = 0; j < NY; ++j) {
            double x = i * dx;
            double y = j * dy;
            file << x << "," << y << "," << u[i][j] << "," << v[i][j] << "\n";
        }
    }
    file.close();
    std::cout << "Saved flow field to " << filename << "\n";
}

//边界条件
void apply_boundary_conditions(Matrix& u, Matrix& v) {

    for (int i = 0; i < NX; ++i) {
        u[i][0] = 0.0;            // 下边界
        u[i][NY - 1] = 1.0;       // 上边界
        v[i][0] = 0.0;
        v[i][NY - 1] = 0.0;
    }
    for (int j = 0; j < NY; ++j) {
        u[0][j] = 0.0;            // 左边界
        u[NX - 1][j] = 0.0;       // 右边界
        //v[0][j] = 0.0;
        //v[NX - 1][j] = 0.0;
    }
    

}

int main() {
    Matrix u = zeros(NX, NY);
    Matrix v = zeros(NX, NY);
    Matrix u_new = u;
    Matrix v_new = v;
    for (int n = 0; n < NSTEPS; ++n) {
        u_new = u;
        v_new = v;

        //中心差分 + Euler 时间推进
        for (int i = 1; i < NX - 1; ++i) {
            for (int j = 1; j < NY - 1; ++j) {
                double du_dx = (u[i+1][j] - u[i-1][j]) / (2 * dx);
                double du_dy = (u[i][j+1] - u[i][j-1]) / (2 * dy);
                double d2u_dx2 = (u[i+1][j] - 2*u[i][j] + u[i-1][j]) / (dx*dx);
                double d2u_dy2 = (u[i][j+1] - 2*u[i][j] + u[i][j-1]) / (dy*dy);

                double dv_dx = (v[i+1][j] - v[i-1][j]) / (2 * dx);
                double dv_dy = (v[i][j+1] - v[i][j-1]) / (2 * dy);
                double d2v_dx2 = (v[i+1][j] - 2*v[i][j] + v[i-1][j]) / (dx*dx);
                double d2v_dy2 = (v[i][j+1] - 2*v[i][j] + v[i][j-1]) / (dy*dy);

                u_new[i][j] = u[i][j] + dt * (
                    - u[i][j]*du_dx 
                    - v[i][j]*du_dy 
                    + nu * (d2u_dx2 + d2u_dy2)
                );
                /*
                v_new[i][j] = v[i][j] + dt * (
                    - u[i][j]*dv_dx 
                    - v[i][j]*dv_dy 
                    + nu * (d2v_dx2 + d2v_dy2)
                );
                */

                v_new[i][j] = v[i][j] - dt * (
                    u[i][j] * (v[i+1][j] - v[i-1][j]) / (2*dx) +
                    v[i][j] * (v[i][j+1] - v[i][j-1]) / (2*dy)
                    );
            }
        }
        
        for (int i = NX/3; i < NX*2/3; ++i) 
        {
            for (int j = NY/3; j < NY*2/3; ++j) 
            {
                v_new[i][j] = 0.1 * sin(i * dx * 10) * sin(j * dy * 10);
            }
        }
        /*
        int cx = NX/2;
        int cy = NY/2;
        v_new[cx][cy] += 0.01;  // 添加持续的垂直扰动
        */
        u = u_new;
        v = v_new;

        apply_boundary_conditions(u, v);

        if (n % 1000 == 0) {
            write_csv(u, v, "flow_" + std::to_string(n) + ".csv");
        }

        std::cout << "Step " << n << " completed.\n";
    }

    return 0;
}
