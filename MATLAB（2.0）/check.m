% 检测当前数独是否合法，result为0则合法，否则不合法
function result = check(A)
    result = 0;
    for num = 1:9
        R = zeros(1,9);
        C = zeros(1,9);
        H = zeros(3,3);
        for i = 1:9
            for j = 1:9
                if A(i,j)==num
                    if i<4
                        row = 1;
                    elseif i<7
                        row = 2;
                    else
                        row = 3;
                    end
                    if j<4
                        col = 1;
                    elseif j<7
                        col = 2;
                    else
                        col = 3;
                    end
                    % 数独行、列或者九宫格内存在重复数字，数独不合法
                    if R(i)==1 || C(j)==1 || H(row,col)==1
                        result = 1;
                        return;
                    else
                        R(i) = 1;
                        C(j) = 1;
                        H(row,col) = 1;
                    end
                end
            end
        end
    end
    return;
end