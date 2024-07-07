; ModuleID = './test/dfg/src/alg3.bc'
source_filename = "self_tests/src_huawei/alg3.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define dso_local noundef zeroext i8 @_Z11alg3_func_1Pii(ptr nocapture noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = add nsw i32 %1, -1
  %4 = mul nsw i32 %3, %1
  %5 = sdiv i32 %4, 2
  %6 = icmp sgt i32 %4, 1
  br i1 %6, label %7, label %9

7:                                                ; preds = %2
  %8 = add i32 %1, -2
  br label %12

9:                                                ; preds = %24, %2
  %10 = and i32 %1, 1
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %37, label %32

12:                                               ; preds = %7, %24
  %13 = phi i32 [ 0, %7 ], [ %30, %24 ]
  %14 = phi i32 [ undef, %7 ], [ %29, %24 ]
  %15 = phi i32 [ undef, %7 ], [ %27, %24 ]
  %16 = getelementptr inbounds i32, ptr %0, i32 %15
  %17 = load i32, ptr %16, align 4, !tbaa !6
  %18 = add nsw i32 %15, 1
  %19 = getelementptr inbounds i32, ptr %0, i32 %18
  %20 = load i32, ptr %19, align 4, !tbaa !6
  %21 = icmp sgt i32 %17, %20
  br i1 %21, label %22, label %24

22:                                               ; preds = %12
  store i32 %20, ptr %16, align 4, !tbaa !6
  %23 = and i32 %17, 255
  store i32 %23, ptr %19, align 4, !tbaa !6
  br label %24

24:                                               ; preds = %22, %12
  %25 = sub i32 %8, %14
  %26 = icmp sge i32 %15, %25
  %27 = select i1 %26, i32 0, i32 %18
  %28 = zext i1 %26 to i32
  %29 = add nsw i32 %14, %28
  %30 = add nuw nsw i32 %13, 1
  %31 = icmp eq i32 %30, %5
  br i1 %31, label %9, label %12, !llvm.loop !10

32:                                               ; preds = %9
  %33 = add nsw i32 %1, 1
  %34 = sdiv i32 %33, 2
  %35 = getelementptr inbounds i32, ptr %0, i32 %34
  %36 = load i32, ptr %35, align 4, !tbaa !6
  br label %46

37:                                               ; preds = %9
  %38 = sdiv i32 %1, 2
  %39 = getelementptr inbounds i32, ptr %0, i32 %38
  %40 = load i32, ptr %39, align 4, !tbaa !6
  %41 = add nsw i32 %38, 1
  %42 = getelementptr inbounds i32, ptr %0, i32 %41
  %43 = load i32, ptr %42, align 4, !tbaa !6
  %44 = add nsw i32 %43, %40
  %45 = sdiv i32 %44, 2
  br label %46

46:                                               ; preds = %37, %32
  %47 = phi i32 [ %36, %32 ], [ %45, %37 ]
  %48 = trunc i32 %47 to i8
  ret i8 %48
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @_Z9alg3_funcPtS_jj(ptr nocapture noundef readonly %0, ptr nocapture noundef writeonly %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #2 {
  %5 = alloca [81 x i32], align 4
  %6 = lshr i32 %2, 1
  %7 = lshr i32 %3, 1
  %8 = mul i32 %7, %6
  %9 = shl i32 %8, 4
  %10 = tail call noalias ptr @malloc(i32 noundef %9) #7
  %11 = add nuw i32 %6, 8
  %12 = add nuw i32 %7, 8
  %13 = mul i32 %12, %11
  %14 = shl i32 %13, 4
  %15 = tail call noalias ptr @malloc(i32 noundef %14) #7
  %16 = mul i32 %3, %2
  %17 = lshr i32 %16, 2
  %18 = icmp ult i32 %16, 4
  br i1 %18, label %23, label %19

19:                                               ; preds = %4
  %20 = shl i32 %8, 1
  %21 = mul i32 %8, 3
  %22 = tail call i32 @llvm.umax.i32(i32 %17, i32 1)
  br label %26

23:                                               ; preds = %26, %4
  %24 = shl i32 %8, 2
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %63, label %66

26:                                               ; preds = %19, %26
  %27 = phi i32 [ 0, %19 ], [ %61, %26 ]
  %28 = udiv i32 %27, %6
  %29 = urem i32 %27, %6
  %30 = shl nuw nsw i32 %28, 1
  %31 = mul i32 %30, %2
  %32 = shl nuw nsw i32 %29, 1
  %33 = add i32 %31, %32
  %34 = getelementptr inbounds i16, ptr %0, i32 %33
  %35 = load i16, ptr %34, align 2, !tbaa !13
  %36 = zext i16 %35 to i32
  %37 = mul i32 %28, %2
  %38 = lshr i32 %37, 1
  %39 = add nuw i32 %38, %29
  %40 = getelementptr inbounds i32, ptr %10, i32 %39
  store i32 %36, ptr %40, align 4, !tbaa !6
  %41 = or i32 %33, 1
  %42 = getelementptr inbounds i16, ptr %0, i32 %41
  %43 = load i16, ptr %42, align 2, !tbaa !13
  %44 = zext i16 %43 to i32
  %45 = add i32 %39, %8
  %46 = getelementptr inbounds i32, ptr %10, i32 %45
  store i32 %44, ptr %46, align 4, !tbaa !6
  %47 = or i32 %30, 1
  %48 = mul i32 %47, %2
  %49 = add i32 %48, %32
  %50 = getelementptr inbounds i16, ptr %0, i32 %49
  %51 = load i16, ptr %50, align 2, !tbaa !13
  %52 = zext i16 %51 to i32
  %53 = add i32 %39, %20
  %54 = getelementptr inbounds i32, ptr %10, i32 %53
  store i32 %52, ptr %54, align 4, !tbaa !6
  %55 = add i32 %49, 1
  %56 = getelementptr inbounds i16, ptr %0, i32 %55
  %57 = load i16, ptr %56, align 2, !tbaa !13
  %58 = zext i16 %57 to i32
  %59 = add i32 %39, %21
  %60 = getelementptr inbounds i32, ptr %10, i32 %59
  store i32 %58, ptr %60, align 4, !tbaa !6
  %61 = add nuw nsw i32 %27, 1
  %62 = icmp eq i32 %61, %22
  br i1 %62, label %23, label %26, !llvm.loop !15

63:                                               ; preds = %66, %23
  %64 = shl i32 %7, 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %112, label %92

66:                                               ; preds = %23, %66
  %67 = phi i32 [ %86, %66 ], [ 0, %23 ]
  %68 = udiv i32 %67, %8
  %69 = udiv i32 %67, %6
  %70 = urem i32 %69, %7
  %71 = urem i32 %67, %6
  %72 = mul i32 %70, %2
  %73 = lshr i32 %72, 1
  %74 = mul i32 %8, %68
  %75 = add i32 %71, %74
  %76 = add i32 %75, %73
  %77 = getelementptr inbounds i32, ptr %10, i32 %76
  %78 = load i32, ptr %77, align 4, !tbaa !6
  %79 = add nuw nsw i32 %70, 4
  %80 = mul i32 %68, %12
  %81 = add i32 %79, %80
  %82 = mul i32 %81, %11
  %83 = add nuw i32 %71, 4
  %84 = add i32 %83, %82
  %85 = getelementptr inbounds i32, ptr %15, i32 %84
  store i32 %78, ptr %85, align 4, !tbaa !6
  %86 = add nuw nsw i32 %67, 1
  %87 = icmp eq i32 %86, %24
  br i1 %87, label %63, label %66, !llvm.loop !16

88:                                               ; preds = %92
  br i1 %65, label %112, label %89

89:                                               ; preds = %88
  %90 = add nsw i32 %6, -1
  %91 = add nuw i32 %6, 4
  br label %117

92:                                               ; preds = %63, %92
  %93 = phi i32 [ %110, %92 ], [ 0, %63 ]
  %94 = udiv i32 %93, %7
  %95 = lshr i32 %93, 2
  %96 = urem i32 %95, %7
  %97 = add nuw nsw i32 %96, 4
  %98 = and i32 %93, 3
  %99 = mul i32 %96, %2
  %100 = lshr i32 %99, 1
  %101 = mul i32 %8, %94
  %102 = add i32 %100, %101
  %103 = getelementptr inbounds i32, ptr %10, i32 %102
  %104 = load i32, ptr %103, align 4, !tbaa !6
  %105 = mul i32 %94, %12
  %106 = add i32 %97, %105
  %107 = mul i32 %106, %11
  %108 = add i32 %107, %98
  %109 = getelementptr inbounds i32, ptr %15, i32 %108
  store i32 %104, ptr %109, align 4, !tbaa !6
  %110 = add nuw nsw i32 %93, 1
  %111 = icmp eq i32 %110, %64
  br i1 %111, label %88, label %92, !llvm.loop !17

112:                                              ; preds = %117, %63, %88
  %113 = shl i32 %11, 4
  %114 = icmp eq i32 %113, 0
  br i1 %114, label %161, label %115

115:                                              ; preds = %112
  %116 = shl i32 %11, 2
  br label %145

117:                                              ; preds = %89, %117
  %118 = phi i32 [ 0, %89 ], [ %137, %117 ]
  %119 = udiv i32 %118, %7
  %120 = lshr i32 %118, 2
  %121 = urem i32 %120, %7
  %122 = add nuw nsw i32 %121, 4
  %123 = and i32 %118, 3
  %124 = mul i32 %121, %2
  %125 = lshr i32 %124, 1
  %126 = mul i32 %8, %119
  %127 = add i32 %90, %126
  %128 = add i32 %127, %125
  %129 = getelementptr inbounds i32, ptr %10, i32 %128
  %130 = load i32, ptr %129, align 4, !tbaa !6
  %131 = mul i32 %119, %12
  %132 = add i32 %122, %131
  %133 = mul i32 %132, %11
  %134 = add i32 %91, %123
  %135 = add i32 %134, %133
  %136 = getelementptr inbounds i32, ptr %15, i32 %135
  store i32 %130, ptr %136, align 4, !tbaa !6
  %137 = add nuw nsw i32 %118, 1
  %138 = icmp eq i32 %137, %64
  br i1 %138, label %112, label %117, !llvm.loop !18

139:                                              ; preds = %145
  br i1 %114, label %161, label %140

140:                                              ; preds = %139
  %141 = shl i32 %11, 2
  %142 = add nuw i32 %7, 4
  %143 = add nuw i32 %7, 3
  %144 = mul i32 %143, %11
  br label %169

145:                                              ; preds = %115, %145
  %146 = phi i32 [ 0, %115 ], [ %159, %145 ]
  %147 = udiv i32 %146, %116
  %148 = udiv i32 %146, %11
  %149 = and i32 %148, 3
  %150 = urem i32 %146, %11
  %151 = mul i32 %13, %147
  %152 = add i32 %151, %150
  %153 = add i32 %152, %116
  %154 = getelementptr inbounds i32, ptr %15, i32 %153
  %155 = load i32, ptr %154, align 4, !tbaa !6
  %156 = mul i32 %149, %11
  %157 = add i32 %152, %156
  %158 = getelementptr inbounds i32, ptr %15, i32 %157
  store i32 %155, ptr %158, align 4, !tbaa !6
  %159 = add nuw nsw i32 %146, 1
  %160 = icmp eq i32 %159, %113
  br i1 %160, label %139, label %145, !llvm.loop !19

161:                                              ; preds = %169, %112, %139
  call void @llvm.lifetime.start.p0(i64 324, ptr nonnull %5) #8
  call void @llvm.memset.p0.i32(ptr noundef nonnull align 4 dereferenceable(324) %5, i8 0, i32 324, i1 false)
  %162 = and i32 %16, -4
  %163 = mul i32 %162, 81
  %164 = icmp eq i32 %163, 0
  br i1 %164, label %186, label %165

165:                                              ; preds = %161
  %166 = mul i32 %8, 81
  %167 = mul i32 %6, 81
  %168 = getelementptr inbounds i32, ptr %5, i32 41
  br label %191

169:                                              ; preds = %140, %169
  %170 = phi i32 [ 0, %140 ], [ %184, %169 ]
  %171 = udiv i32 %170, %141
  %172 = udiv i32 %170, %11
  %173 = and i32 %172, 3
  %174 = add i32 %142, %173
  %175 = urem i32 %170, %11
  %176 = mul i32 %13, %171
  %177 = add i32 %176, %175
  %178 = add i32 %177, %144
  %179 = getelementptr inbounds i32, ptr %15, i32 %178
  %180 = load i32, ptr %179, align 4, !tbaa !6
  %181 = mul i32 %174, %11
  %182 = add i32 %177, %181
  %183 = getelementptr inbounds i32, ptr %15, i32 %182
  store i32 %180, ptr %183, align 4, !tbaa !6
  %184 = add nuw nsw i32 %170, 1
  %185 = icmp eq i32 %184, %113
  br i1 %185, label %161, label %169, !llvm.loop !20

186:                                              ; preds = %245, %161
  br i1 %18, label %248, label %187

187:                                              ; preds = %186
  %188 = shl i32 %8, 1
  %189 = mul i32 %8, 3
  %190 = tail call i32 @llvm.umax.i32(i32 %17, i32 1)
  br label %249

191:                                              ; preds = %165, %245
  %192 = phi i32 [ 0, %165 ], [ %246, %245 ]
  %193 = udiv i32 %192, %166
  %194 = udiv i32 %192, %167
  %195 = urem i32 %194, %7
  %196 = udiv i32 %192, 81
  %197 = urem i32 %196, %6
  %198 = urem i32 %192, 81
  %199 = trunc i32 %198 to i8
  %200 = udiv i8 %199, 9
  %201 = zext i8 %200 to i32
  %202 = urem i8 %199, 9
  %203 = zext i8 %202 to i32
  %204 = add nuw i32 %195, %201
  %205 = mul i32 %193, %12
  %206 = add i32 %204, %205
  %207 = mul i32 %206, %11
  %208 = add nuw nsw i32 %197, %203
  %209 = add i32 %208, %207
  %210 = getelementptr inbounds i32, ptr %15, i32 %209
  %211 = load i32, ptr %210, align 4, !tbaa !6
  %212 = mul nuw nsw i32 %201, 9
  %213 = add nuw nsw i32 %212, %203
  %214 = getelementptr inbounds [81 x i32], ptr %5, i32 0, i32 %213
  store i32 %211, ptr %214, align 4, !tbaa !6
  %215 = icmp eq i32 %198, 80
  br i1 %215, label %216, label %245

216:                                              ; preds = %191, %228
  %217 = phi i32 [ %234, %228 ], [ 0, %191 ]
  %218 = phi i32 [ %233, %228 ], [ undef, %191 ]
  %219 = phi i32 [ %231, %228 ], [ undef, %191 ]
  %220 = getelementptr inbounds i32, ptr %5, i32 %219
  %221 = load i32, ptr %220, align 4, !tbaa !6
  %222 = add nsw i32 %219, 1
  %223 = getelementptr inbounds i32, ptr %5, i32 %222
  %224 = load i32, ptr %223, align 4, !tbaa !6
  %225 = icmp sgt i32 %221, %224
  br i1 %225, label %226, label %228

226:                                              ; preds = %216
  store i32 %224, ptr %220, align 4, !tbaa !6
  %227 = and i32 %221, 255
  store i32 %227, ptr %223, align 4, !tbaa !6
  br label %228

228:                                              ; preds = %226, %216
  %229 = sub i32 79, %218
  %230 = icmp sge i32 %219, %229
  %231 = select i1 %230, i32 0, i32 %222
  %232 = zext i1 %230 to i32
  %233 = add nsw i32 %218, %232
  %234 = add nuw nsw i32 %217, 1
  %235 = icmp eq i32 %234, 3240
  br i1 %235, label %236, label %216, !llvm.loop !10

236:                                              ; preds = %228
  %237 = load i32, ptr %168, align 4, !tbaa !6
  %238 = and i32 %237, 255
  %239 = mul i32 %195, %2
  %240 = lshr i32 %239, 1
  %241 = mul i32 %8, %193
  %242 = add i32 %197, %241
  %243 = add i32 %242, %240
  %244 = getelementptr inbounds i32, ptr %10, i32 %243
  store i32 %238, ptr %244, align 4, !tbaa !6
  br label %245

245:                                              ; preds = %191, %236
  %246 = add nuw nsw i32 %192, 1
  %247 = icmp eq i32 %246, %163
  br i1 %247, label %186, label %191, !llvm.loop !21

248:                                              ; preds = %249, %186
  tail call void @free(ptr noundef %10) #8
  tail call void @free(ptr noundef %15) #8
  call void @llvm.lifetime.end.p0(i64 324, ptr nonnull %5) #8
  ret void

249:                                              ; preds = %187, %249
  %250 = phi i32 [ 0, %187 ], [ %284, %249 ]
  %251 = udiv i32 %250, %6
  %252 = urem i32 %250, %6
  %253 = mul i32 %251, %2
  %254 = lshr i32 %253, 1
  %255 = add nuw i32 %254, %252
  %256 = getelementptr inbounds i32, ptr %10, i32 %255
  %257 = load i32, ptr %256, align 4, !tbaa !6
  %258 = trunc i32 %257 to i16
  %259 = shl nuw nsw i32 %251, 1
  %260 = mul i32 %259, %2
  %261 = shl nuw nsw i32 %252, 1
  %262 = add i32 %260, %261
  %263 = getelementptr inbounds i16, ptr %1, i32 %262
  store i16 %258, ptr %263, align 2, !tbaa !13
  %264 = add i32 %255, %8
  %265 = getelementptr inbounds i32, ptr %10, i32 %264
  %266 = load i32, ptr %265, align 4, !tbaa !6
  %267 = trunc i32 %266 to i16
  %268 = or i32 %262, 1
  %269 = getelementptr inbounds i16, ptr %1, i32 %268
  store i16 %267, ptr %269, align 2, !tbaa !13
  %270 = add i32 %255, %188
  %271 = getelementptr inbounds i32, ptr %10, i32 %270
  %272 = load i32, ptr %271, align 4, !tbaa !6
  %273 = trunc i32 %272 to i16
  %274 = or i32 %259, 1
  %275 = mul i32 %274, %2
  %276 = add i32 %275, %261
  %277 = getelementptr inbounds i16, ptr %1, i32 %276
  store i16 %273, ptr %277, align 2, !tbaa !13
  %278 = add i32 %255, %189
  %279 = getelementptr inbounds i32, ptr %10, i32 %278
  %280 = load i32, ptr %279, align 4, !tbaa !6
  %281 = trunc i32 %280 to i16
  %282 = add i32 %276, 1
  %283 = getelementptr inbounds i16, ptr %1, i32 %282
  store i16 %281, ptr %283, align 2, !tbaa !13
  %284 = add nuw nsw i32 %250, 1
  %285 = icmp eq i32 %284, %190
  br i1 %285, label %248, label %249, !llvm.loop !22
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i32 noundef) local_unnamed_addr #3

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i32(ptr nocapture writeonly, i8, i32, i1 immarg) #4

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr nocapture noundef) local_unnamed_addr #5

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umax.i32(i32, i32) #6

attributes #0 = { mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #5 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #6 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #7 = { nounwind allocsize(0) }
attributes #8 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!"Ubuntu clang version 16.0.6 (++20231112100421+7cbf1a259152-1~exp1~20231112100514.107)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"int", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = distinct !{!10, !11, !12}
!11 = !{!"llvm.loop.mustprogress"}
!12 = !{!"llvm.loop.unroll.disable"}
!13 = !{!14, !14, i64 0}
!14 = !{!"short", !8, i64 0}
!15 = distinct !{!15, !11, !12}
!16 = distinct !{!16, !11, !12}
!17 = distinct !{!17, !11, !12}
!18 = distinct !{!18, !11, !12}
!19 = distinct !{!19, !11, !12}
!20 = distinct !{!20, !11, !12}
!21 = distinct !{!21, !11, !12}
!22 = distinct !{!22, !11, !12}
