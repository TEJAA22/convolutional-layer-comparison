C++ Source file :

#include <iostream>
#include <vector>
#include <thread>

void convolve(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& kernel,
              std::vector<std::vector<int>>& result, int start_row, int end_row) {
    int image_height = image.size();
    int image_width = image[0].size();
    int kernel_height = kernel.size();
    int kernel_width = kernel[0].size();
    int result_height = image_height - kernel_height + 1;
    int result_width = image_width - kernel_width + 1;

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < result_width; ++j) {
            for (int ki = 0; ki < kernel_height; ++ki) {
                for (int kj = 0; kj < kernel_width; ++kj) {
                    result[i][j] += image[i + ki][j + kj] * kernel[ki][kj];
                }
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> image = {{1, 2, 1, 2},
                                            {2, 1, 2, 1},
                                            {1, 2, 1, 2},
                                            {2, 1, 2, 1}};

    std::vector<std::vector<int>> kernel = {{1, 0},
                                             {0, 1}};

    int num_threads = std::thread::hardware_concurrency();
    int rows_per_thread = image.size() / num_threads;
    std::vector<std::thread> threads;

    std::vector<std::vector<int>> result(image.size() - kernel.size() + 1, std::vector<int>(image[0].size() - kernel[0].size() + 1, 0));

    for (int i = 0; i < num_threads; ++i) {
        int start_row = i * rows_per_thread;
        int end_row = (i == num_threads - 1) ? image.size() : start_row + rows_per_thread;
        threads.emplace_back(convolve, std::ref(image), std::ref(kernel), std::ref(result), start_row, end_row);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Result of convolution:" << std::endl;
    for (const auto& row : result) {
        for (int pixel : row) {
            std::cout << pixel << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
