const WASM_PATH = "/wasm";

const loadWasm = async (file: string, canvas: HTMLCanvasElement) => {
  const wasmModule = await import(`${WASM_PATH}/${file}.js`) as any;
  await wasmModule.default({
    canvas,
    localeFile: () => `${WASM_PATH}/${file}.wasm`,
  });
};

export default loadWasm;