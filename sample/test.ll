; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@a = external global [1024 x [1024 x float]], align 16
@b = external global [1024 x [1024 x float]], align 16
@c = external global [1024 x [1024 x float]], align 16
@d = external global [1024 x [1024 x float]], align 16

; Function Attrs: noinline nounwind uwtable
define void @calc() local_unnamed_addr #0 {
entry:
  %0 = tail call float* @__spd_alloc_stream(i64 2097152) #1
  %1 = tail call float* @__spd_alloc_stream(i64 2097152) #1
  tail call void @__spd_pack_contiguous(float* %0, i32 0, i32 2, float* getelementptr inbounds ([1024 x [1024 x float]], [1024 x [1024 x float]]* @a, i64 0, i64 0, i64 0), i64 1048576) #1
  tail call void @__spd_pack_contiguous(float* %0, i32 1, i32 2, float* getelementptr inbounds ([1024 x [1024 x float]], [1024 x [1024 x float]]* @b, i64 0, i64 0, i64 0), i64 1048576) #1
  tail call void @__spd_run_kernel(float* %0, i64 2097152, float* %1, i64 2097152) #1
  tail call void @__spd_unpack_contiguous(float* getelementptr inbounds ([1024 x [1024 x float]], [1024 x [1024 x float]]* @c, i64 0, i64 0, i64 0), i64 1048576, float* %1, i32 0, i32 2) #1
  tail call void @__spd_unpack_contiguous(float* getelementptr inbounds ([1024 x [1024 x float]], [1024 x [1024 x float]]* @d, i64 0, i64 0, i64 0), i64 1048576, float* %1, i32 1, i32 2) #1
  tail call void @__spd_free_stream(float* %0) #1
  tail call void @__spd_free_stream(float* %1) #1
  ret void
}

declare float* @__spd_alloc_stream(i64) local_unnamed_addr

declare void @__spd_pack_contiguous(float*, i32, i32, float*, i64) local_unnamed_addr

declare void @__spd_run_kernel(float*, i64, float*, i64) local_unnamed_addr

declare void @__spd_unpack_contiguous(float*, i64, float*, i32, i32) local_unnamed_addr

declare void @__spd_free_stream(float*) local_unnamed_addr

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 5.0.0 (tags/RELEASE_500/final)"}
