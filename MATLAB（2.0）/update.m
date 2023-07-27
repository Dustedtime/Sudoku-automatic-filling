% 根据传进的数独矩阵更新B
function [A,B] = update(A,B)
    for i = 1:9
        for j = 1:9
            % 元素大于零，表示第i行第j列数独格子填有数字
            if A(i,j)>0
                % 该格子所在的行和列所有格子皆不能再填写A(i,j)
                for k = 1:9
                    B(i,k,A(i,j)) = 0;
                    B(k,j,A(i,j)) = 0;
                end
                % 求该格子所在的九宫格行坐标和列坐标范围
                if i<4
                    row_start = 1;
                    row_end = 3;
                elseif i<7
                    row_start = 4;
                    row_end = 6;
                else
                    row_start = 7;
                    row_end = 9;
                end
                if j<4
                    col_start = 1;
                    col_end = 3;
                elseif j<7
                    col_start = 4;
                    col_end = 6;
                else
                    col_start = 7;
                    col_end = 9;
                end
                % 该格子所在的九宫格所有格子皆不能再填写A(i,j)
                for row = row_start:row_end
                    for col = col_start:col_end
                        B(row,col,A(i,j)) = 0;
                    end
                end
            end
        end
    end

end