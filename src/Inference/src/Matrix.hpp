#pragma once

/// <summary>
/// 在推理后进行解析数据，因为数据按照列优先排列，但是读取要按照行优先解析
/// 主要是为了减少transpose 操作，优化性能
/// </summary>
/// <typeparam name="T"></typeparam>
namespace Inference
{
    template <typename T>
    class Matrix {
    private:
        const T* data;        // 原始数据
        int rows;       // 行数
        int cols;       // 列数
        bool isColumnMajor;  // 是否为列优先存储

    public:
        // 构造函数，默认按行优先存储
        Matrix(const T* data, int rows, int cols, bool isColumnMajor = false)
            : data(data), rows(rows), cols(cols), isColumnMajor(isColumnMajor) {}

        // 获取元素 根据存储方式不同计算偏移

        T Get(int i, int j) const {
            return isColumnMajor ? static_cast<T>(data[j * rows + i]) : static_cast<T>(data[i * cols + j]);
        }

        int Rows() const {
            return rows;
        }

        int Cols() const {
            return cols;
        }

        void GetMaxValueWithIndexCol(int col, int skip, T& maxValue, int& maxIndex) const {
            maxValue = 0;
            maxIndex = -1;
            if (col < 0 || col >= cols) return;
            

            // 遍历列中的数据
            for (int row = 0; row + skip < rows; ++row) {
                T currentValue = Get(row + skip, col);
                if (currentValue > maxValue) {
                    maxValue = currentValue;
                    maxIndex = row;
                }
            }
        }

        // 按行查找最大值及其索引，跳过指定数量的值
        void GetMaxValueWithIndexRow(int row, int skip, T& maxValue, int& maxIndex) const {
            maxValue = 0;
            maxIndex = -1;
            if (row < 0 || row >= rows) return;
            
            // 遍历行中的数据
            for (int col = 0; col + skip < cols; ++col) {
                T currentValue = Get(row, col + skip);
                if (currentValue > maxValue) {
                    maxValue = currentValue;
                    maxIndex = col; 
                }
            }
        }
    };



} // namespace Inference
